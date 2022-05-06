#define THERMO 34

#define RBUTTON 33
#define GBUTTON 32
#define BBUTTON 35

#define RLED 26
#define GLED 27
#define BLED 14

#define LEDC_CHANNEL_0 0
#define LEDC_CHANNEL_1 1
#define LEDC_CHANNEL_2 2

#define LEDC_BASE_FREQ 5000
#define LEDC_BASE_BIT 8

#define MAXVALUEUINT32 255
#define MAXDUTY 255

uint32_t rDuty,gDuty,bDuty;

double thermoVal2Degree(uint32_t thermoVal,uint8_t bits,float thermoRefVolt,float actRefVolt,uint16_t degRange);
void updateDuty(double degree);
uint32_t calcDuty(uint32_t value, uint32_t dutyMax,uint32_t valueMax);
