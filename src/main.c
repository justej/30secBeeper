#include <stm8s_gpio.h>

#define resetBit(p, b)      do {(p) &= ~(b);} while (0)
#define setBit(p, b)        do {(p) |= (b);} while (0)
#define testBit(p, b)       ((p) & (1 << (b)))
#define testMask(p, b)      (((p) & (b)) == b) 

#define PORT_SOUND_GEN_N    GPIOB
#define PIN_SOUND_GEN_N     GPIO_PIN_5

#define PORT_SOUND_GEN_P    GPIOC
#define PIN_SOUND_GEN_P     GPIO_PIN_3

/* Private function prototypes -----------------------------------------------*/
static void GPIO_Config();

static void delay_ms(uint32_t);
static void die();

void main(void) {
    GPIO_Config();

    resetBit(PORT_SOUND_GEN_N->ODR, PIN_SOUND_GEN_N);

    setBit(PORT_SOUND_GEN_P->ODR, PIN_SOUND_GEN_P);
    delay_ms(1000);
    resetBit(PORT_SOUND_GEN_P->ODR, PIN_SOUND_GEN_P);

    delay_ms(29000);

    setBit(PORT_SOUND_GEN_P->ODR, PIN_SOUND_GEN_P);
    delay_ms(3000);
    resetBit(PORT_SOUND_GEN_P->ODR, PIN_SOUND_GEN_P);

    die();
}

// Configure outputs
static void GPIO_Config() {
    GPIO_Init(PORT_SOUND_GEN_N, (GPIO_Pin_TypeDef)PIN_SOUND_GEN_N, GPIO_MODE_OUT_PP_LOW_FAST);
    GPIO_Init(PORT_SOUND_GEN_P, (GPIO_Pin_TypeDef)PIN_SOUND_GEN_P, GPIO_MODE_OUT_PP_LOW_FAST);
}

static void delay_ms(uint32_t ms) {
    while (ms-- > 0) {
        volatile uint16_t i;
        for (i = F_CPU / 11182 / 8; i > 0; i--) {
            // do nothing
        }
    }
}

static void die() {
    // stop CPU core here
    while(1) {
        halt();
    }
}

void assert_failed(uint8_t* file, uint32_t line) {
    die();
}
