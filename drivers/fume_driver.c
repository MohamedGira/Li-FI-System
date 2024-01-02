#include "fume_driver.h"

void Fume_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeADC(FUME_PORT_BASE, FUME_PIN);

    // Configure ADC0 sequencer 3 for single sample
    ADCSequenceDisable(ADC0_BASE, FUME_SEQUENCER);
    ADCSequenceConfigure(ADC0_BASE, FUME_SEQUENCER, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, FUME_SEQUENCER, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END); // PE3 as input
    ADCSequenceEnable(ADC0_BASE, FUME_SEQUENCER);
}

uint32_t Fume_value()
{
    uint32_t adcValue;

    ADCIntClear(ADC0_BASE, FUME_SEQUENCER);
    ADCProcessorTrigger(ADC0_BASE, FUME_SEQUENCER);

    // Wait for ADC conversion to complete
    while (!ADCIntStatus(ADC0_BASE, FUME_SEQUENCER, false))
        ;

    // Read ADC value
    ADCSequenceDataGet(ADC0_BASE, FUME_SEQUENCER, &adcValue);
    return adcValue;
}
