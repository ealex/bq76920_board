
#include <Wire.h>
#include "bq76920.h"
#include "settings.h"
#include "registers.h"

//remote debug stuff
//#include <WiFiUdp.h>
//#include <WiFi.h>
//#include <ArduinoOTA.h>
//#define HOST_NAME "remotedebug"
//#include "RemoteDebug.h"
//RemoteDebug Debug;
//#define WIFI_SSID "42"  // your network SSID (name)
//#define WIFI_PASS "nu e parola la wireless4321"  // your network key
//uint32_t mTimeToSec = 0;
//uint32_t mTimeSeconds = 0;

//BT serial 
#include "BluetoothSerial.h"
#include "Arduino_DebugUtils.h"
#include "esp_system.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;



// BMS variables and defines
const int ledPin = 5;
#define BMS_ALERT_PIN 2     // attached to interrupt INT0
#define BMS_BOOT_PIN 0      // connected to TS1 input
#define BMS_I2C_ADDRESS 0x08
#define SDA_PIN 21
#define SCL_PIN 22

unsigned long previousMillisRefresh = 0;        // will store last time LED was updated
const long intervalRefresh = 100;           // interval at which to blink (milliseconds)
unsigned long previosuMilisDisplay = 0;
const long intervalDisplay = 10000;           // interval at which to blink (milliseconds)

bq76920 BMS(BMS_I2C_ADDRESS,true);
static bq76920::condensed_afe_data afe_data;
settings SETTINGS;


//interrupt
const byte interruptPin = 25;
volatile int interruptCounter = 0;
int numberOfInterrupts = 0;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR handleInterrupt() {
  portENTER_CRITICAL_ISR(&mux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&mux);
}

// cell balance control
unsigned long previosuBalanceMilis = 0;
const long intervalBalance = 30000; // once every 30s
static float balanceTarget = 0;
void balanceHandle(void);

// charge - discharge state detection
typedef enum {
  idle = 0,
  charging,
  discharging
} charge_discharge_type;
static charge_discharge_type ch_disch_state = idle;
static uint8_t ch_counter = 0;
static uint8_t disch_counter = 0;


// command decoder
String commandBuffer = "";
String lastCommand = "";
boolean newCommand = false;


void setup() {
  Serial.begin(115200);
  while (!Serial);

  pinMode(ledPin, OUTPUT);

  // configure AFE
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, RISING);

  afe_data.enabled_cells = SETTINGS.enabled_cells;
  BMS.init(0, 0, SDA_PIN, SCL_PIN, 100000);
  BMS.setSenseResistor(SETTINGS.current_sense_resistor);
  BMS.setCurrentProtection( SETTINGS.current_protection_range, 
    SETTINGS.current_protection_scd_delay, SETTINGS.current_protection_scd_mv,
    SETTINGS.current_protection_ocd_delay, SETTINGS.current_protection_ocd_mv);
  BMS.setOvUvProtection(SETTINGS.cell_uv_delay, SETTINGS.cell_uv_limit, SETTINGS.cell_ov_delay, SETTINGS.cell_ov_limit);
  BMS.resetErrorCondition(BMS.error_all);
  BMS.disableCharging();
  BMS.disableDischarging();
  BMS.enableBalancingPin(BMS.balance_none);
  afe_data.uv_limit_actual = BMS.getUvLimitActual();
  afe_data.ov_limit_actual = BMS.getOvLimitActual();

  Serial.println("AFE Start-up done");
  
#if 0
  // configure DEBUG
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println("");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Register host name in WiFi and mDNS
  Debug.begin(HOST_NAME); // Initialize the WiFi server
  Debug.setResetCmdEnabled(true); // Enable the reset command
  Debug.showProfiler(true); // Profiler (Good to measure times, to optimize codes)
  Debug.showColors(true); // Colors

  String helpCmd = "status - status dump from AFE\r\n";
  helpCmd.concat("enable - connects the output\r\n");
  helpCmd.concat("disable - isolates the cells\r\n");
  helpCmd.concat("shipmode - turns off the entire board\r\n");

  Debug.setHelpProjectsCmds(helpCmd);
  Debug.setCallBackProjectCmds(&processCmdRemoteDebug);
#endif
#if 1
  SerialBT.begin("esp32BMS");
  Debug.timestampOn();
  Debug.setDebugOutputStream(&SerialBT);
#endif
  Serial.println();
  Serial.println();
  Serial.printf("Cell0,\tCell1,\tCell2,\tCell3,\tCell4,\tTV,\tI,\tInstPW,\t\tTemp,\tStat\r\n");
}


void loop() {
  unsigned long currentMillis = millis();
  uint8_t statusReg;
  uint32_t pInst;

  // info dump task
  if (currentMillis - previosuMilisDisplay >= intervalDisplay) {
    previosuMilisDisplay = currentMillis;
    /*
    for(uint8_t index = 0; index < SETTINGS.max_number_of_cells; index++){
      Debug.print(DBG_INFO,"Cell %d: %fV\r\n", index, afe_data.cells[index]);
    }
    Debug.print(DBG_INFO,"Total voltage: %fV\r\n",afe_data.total_voltage);
    Debug.print(DBG_INFO,"Total current: %fA\r\n",afe_data.system_current);
    Debug.print(DBG_INFO,"Instantaneous power: %fW\r\n",afe_data.inst_power);
    Debug.print(DBG_INFO,"Chip temperature: %fdegC\r\n",afe_data.die_temperature);
    Debug.print(DBG_INFO,"UV Limit : %fV\r\n",afe_data.uv_limit_actual);
    Debug.print(DBG_INFO,"OV Limit : %fV\r\n",afe_data.ov_limit_actual);
    Debug.print(DBG_INFO,"STATUS   : 0b%s\r\n", BMS.byte2char(afe_data.status_reg));
    Debug.print(DBG_INFO,"CELLBAL1 : 0b%s\r\n", BMS.byte2char(BMS.readRegister(CELLBAL1)));
    Debug.print(DBG_INFO,"SYS_CTRL1: 0b%s\r\n", BMS.byte2char(BMS.readRegister(SYS_CTRL1)));
    Debug.print(DBG_INFO,"SYS_CTRL2: 0b%s\r\n", BMS.byte2char(BMS.readRegister(SYS_CTRL2)));
    */
  }

  if(interruptCounter>0){
    portENTER_CRITICAL(&mux);
    interruptCounter--;
    portEXIT_CRITICAL(&mux);

    digitalWrite(ledPin, HIGH);
    // read and clean status byte
    afe_data = BMS.readAllDataAtOnce(afe_data);
    BMS.resetErrorCondition(BMS.error_all);

    // shut down the outputs on all events
    if(0b00111111&afe_data.status_reg) {
      //BMS.disableCharging();
      //BMS.disableDischarging();
    }

    if(0b00100000&afe_data.status_reg) {
      Debug.print(DBG_ERROR,"DEVICE_XREADY\r\n");
    }
    if(0b00010000&afe_data.status_reg) {
       Debug.print(DBG_ERROR,"OVRD_ALERT\r\n");
    }
    if(0b00001000&afe_data.status_reg) {
       Debug.print(DBG_ERROR,"UV\r\n");
      // check if I need to shutdown
      for(uint8_t index=0; index < SETTINGS.max_number_of_cells; index++) {
        if((0x01<<index)&SETTINGS.enabled_cells) {
          if(afe_data.cells[index]<SETTINGS.cell_uv_shutdown_limit) {
            Debug.print(DBG_ERROR,"Cell %d unde limit: %f < %f\r\nSHUTDOWN\r\n", index, afe_data.cells[index],SETTINGS.cell_uv_shutdown_limit );
            BMS.shutDownBms();
          }
        }
      }
    }
    if(0b00000100&afe_data.status_reg) {
       Debug.print(DBG_ERROR,"OV\r\n");
    }
    if(0b00000010&afe_data.status_reg) {
      Debug.print(DBG_ERROR,"SCD\r\n");
    }
    if(0b00000001&afe_data.status_reg) {
      Debug.print(DBG_ERROR,"OCD\r\n");
    }
    
    afe_data.inst_power = BMS.computeInstPower(afe_data);

/* is it really needed ? maybe signal it as an OS semafore or global flag
    // determine charge / discharge operations
    if(afe_data.system_current > 0) {
      if(afe_data.system_current > SETTINGS.charge_discharge_ch_threshold) {
        if(ch_counter==SETTINGS.charge_discharge_ch_limit) {
          rdebugW("STATE CHARGING\r\n");
          ch_disch_state = charging;
          ch_counter = SETTINGS.charge_discharge_ch_limit;
        } else {
          ch_disch_state = idle;
          ch_counter ++;
        }
      } else {
        if(charging==ch_disch_state) {
          rdebugW("STATE IDLE\r\n");
        }
        if(discharging==ch_disch_state) {
          rdebugW("STATE IDLE\r\n");
        }
        ch_disch_state = idle;
        ch_counter = 0;
      }
    } else if (0==afe_data.system_current) { // battery is IDLE
      if(charging==ch_disch_state) {
          rdebugW("STATE IDLE\r\n");
      }
      ch_disch_state = idle;
      ch_counter = 0;
      disch_counter = 0;
    } else { 
      if( SETTINGS.charge_discharge_disch_threshold > afe_data.system_current) {
        if(disch_counter>=SETTINGS.charge_discharge_disch_limit) {
          rdebugW("STATE DISCHARGING\r\n");
          ch_disch_state = discharging;
          disch_counter = SETTINGS.charge_discharge_disch_limit;
        } else {
          ch_disch_state = idle;
          disch_counter ++;
        }
      } else {
        if(discharging==ch_disch_state) {
          rdebugW("STATE IDLE\r\n");
        }
        ch_disch_state = idle;
        disch_counter = 0;
      }
    }
*/    
    delay(50);   
    digitalWrite(ledPin, LOW); 
  }

  // time the cell balancing task
  if (currentMillis - previosuBalanceMilis >= intervalBalance) {
    previosuBalanceMilis = currentMillis;
    balanceHandle();
    //Serial.println("BAL");
  }

  //process input data to check for commands
  if(0<SerialBT.available()) {
    // got some serial data
    int serialData = SerialBT.read();
    if('\n'==serialData) {
      processCmdRemoteDebug(commandBuffer);
      commandBuffer = "";
    } else {
      commandBuffer += (char)serialData;
      //Serial.println(commandBuffer);
    }
  }
  
  yield(); 
}


void processCmdRemoteDebug(String lastCmd) {

  if(lastCmd.startsWith("sta")) {
    for(uint8_t index = 0; index < SETTINGS.max_number_of_cells; index++){
      Debug.print(DBG_INFO,"Cell %d: %fV\r\n", index, afe_data.cells[index]);
    }
    Debug.print(DBG_INFO,"Total voltage: %fV\r\n",afe_data.total_voltage);
    Debug.print(DBG_INFO,"Total current: %fA\r\n",afe_data.system_current);
    Debug.print(DBG_INFO,"Instantaneous power: %fW\r\n",afe_data.inst_power);
    Debug.print(DBG_INFO,"Chip temperature: %fdegC\r\n",afe_data.die_temperature);
    Debug.print(DBG_INFO,"UV Limit : %fV\r\n",afe_data.uv_limit_actual);
    Debug.print(DBG_INFO,"OV Limit : %fV\r\n",afe_data.ov_limit_actual);
    Debug.print(DBG_INFO,"STATUS   : 0b%s\r\n", BMS.byte2char(afe_data.status_reg));
    Debug.print(DBG_INFO,"CELLBAL1 : 0b%s\r\n", BMS.byte2char(BMS.readRegister(CELLBAL1)));
    Debug.print(DBG_INFO,"SYS_CTRL1: 0b%s\r\n", BMS.byte2char(BMS.readRegister(SYS_CTRL1)));
    Debug.print(DBG_INFO,"SYS_CTRL2: 0b%s\r\n", BMS.byte2char(BMS.readRegister(SYS_CTRL2)));
  } else if(lastCmd.startsWith("ena")) {
    BMS.enableCharging();
    BMS.enableDischarging();
    Debug.print(DBG_INFO,"outputs ENABLED\r\n");
  } else if(lastCmd.startsWith("dis")) {
    BMS.disableCharging();
    BMS.disableDischarging();
    Debug.print(DBG_INFO,"outputs DISABLED\r\n");
  } else if(lastCmd.startsWith("shipmode")) {
    Debug.print(DBG_INFO,"SHUTTING DOWN SYSTEM\r\n");
    BMS.shutDownBms();
  } else if(lastCmd.startsWith("bal")) {
    lastCmd.replace(String("bal"),String(""));
    lastCmd.trim();
    balanceTarget = lastCmd.toFloat();
    if(SETTINGS.minCellValue<balanceTarget) {
      Debug.print(DBG_WARNING,"Balance ON for %fV\r\n",balanceTarget);
    } else {
      Debug.print(DBG_WARNING,"Balance OFF\r\n");
    }
  }
}



void balanceHandle(void) {
  const float desiredDelta = 0.050;
  float maxValue = 0; // start from 0
  float minValue = (float)10; // no cell can get this high
  float actualDelta;
  uint8_t selectedCell;
  
  if(SETTINGS.minCellValue<balanceTarget) {
    // parse all cells and get max / min and delta
    for(uint8_t index = 0; index < SETTINGS.max_number_of_cells; index ++) {
      if((0x01<<index)&SETTINGS.enabled_cells) {
        if(afe_data.cells[index] > maxValue) {
          maxValue = afe_data.cells[index];
          selectedCell = index; // select the cell with the highest voltage
        }
        if(afe_data.cells[index] < minValue) {
          minValue = afe_data.cells[index];
        }
      }
    }

    actualDelta = maxValue - balanceTarget;
    if(actualDelta > 0) {
      Debug.print(DBG_INFO,"Max cell: %f\tMin cell: %f\tCell Delta: %f\tTarget delta: %f\r\n", maxValue, minValue, maxValue-minValue, actualDelta);
      Debug.print(DBG_INFO,"Selected cell %d, from %f to %f volts\r\n", selectedCell, afe_data.cells[selectedCell], balanceTarget);
      switch(selectedCell) {
        case 0:
          BMS.enableBalancingPin(BMS.balance_c0);
          break;
        case 1:
          BMS.enableBalancingPin(BMS.balance_c1);
          break;
        case 2:
          BMS.enableBalancingPin(BMS.balance_c2);
          break;
        case 3:
          BMS.enableBalancingPin(BMS.balance_c3);
          break;
        case 4:
          BMS.enableBalancingPin(BMS.balance_c4);
          break;
        default:
          BMS.enableBalancingPin(BMS.balance_none );
      }
    } else {
      //rdebugI("balancer: cells under target voltage, nothing to do\r\n");
      BMS.enableBalancingPin(BMS.balance_none );
    }
  } else {
    // it's disabled, update the registers to be sure
    BMS.enableBalancingPin(BMS.balance_none );
  }
}
