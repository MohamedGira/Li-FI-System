#include "ldr_driver.h"

/*sets PE2, along with adc0 ans sequencer0 for LDR sensor*/
void Ldr_Init()
{
    // Similar setup as Fume_Init but for LDR sensor using PE2 (AIN1)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeADC(LDR_PORT_BASE, LDR_PIN);

    ADCSequenceDisable(ADC0_BASE, LDR_SEQUENCER);
    ADCSequenceConfigure(ADC0_BASE, LDR_SEQUENCER, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, LDR_SEQUENCER, 0, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END); // PE2 as input (AIN1)
    ADCSequenceEnable(ADC0_BASE, LDR_SEQUENCER);
}

uint32_t Ldr_value()
{
    uint32_t adcValue;

    ADCIntClear(ADC0_BASE, LDR_SEQUENCER);
    ADCProcessorTrigger(ADC0_BASE, LDR_SEQUENCER);

    // Wait for ADC conversion to complete
    while (!ADCIntStatus(ADC0_BASE, LDR_SEQUENCER, false))
        ;

    // Read ADC value
    ADCSequenceDataGet(ADC0_BASE, LDR_SEQUENCER, &adcValue);
    return adcValue;
}
