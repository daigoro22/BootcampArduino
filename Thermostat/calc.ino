uint32_t rValue=0,gValue=0,bValue=0;
#define DEGNUM 5
const int DegreesForLED[DEGNUM] = {5,10,20,30,35};
const int RForLED[] = {0,0,0,239,255};
const int GForLED[] = {0,255,255,129,0};
const int BForLED[] = {255,255,51,15,0};

uint32_t calcDuty(uint32_t value, uint32_t dutyMax=MAXDUTY,uint32_t valueMax=MAXVALUEUINT32){
  return (dutyMax/valueMax)*min(value,valueMax);
}

double thermoVal2Degree(uint32_t thermoVal,uint8_t bits,float thermoRefVolt,float actRefVolt,uint16_t degRange){
  return (degRange * thermoVal) / (1<<bits) * (thermoRefVolt/actRefVolt);
}

void updateDuty(double degree){
  rDuty=calcDuty(rValue);
  gDuty=calcDuty(gValue);
  bDuty=calcDuty(bValue);
 
  for(int i=0;i<DEGNUM;i++){
    if(degree<DegreesForLED[i]){
      rValue = RForLED[i];
      gValue = GForLED[i];
      bValue = BForLED[i];
      return;
    }
  }
}
