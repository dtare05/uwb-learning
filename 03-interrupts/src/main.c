#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#define SLEEP_TIME_MS 20

static const struct gpio_dt_spec button =
    GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);
static const struct gpio_dt_spec led =
    GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
int main(void)
    {
    if (!gpio_is_ready_dt(&led) || !gpio_is_ready_dt(&button)) {
    return 0;
    }

    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&button, GPIO_INPUT);
    while (1) {
        int press = gpio_pin_get_dt(&button);
        printk("Button = %d\n", press);
        if(press == 1){
            gpio_pin_set_dt(&led, 1);
        } else{
            gpio_pin_set_dt(&led, 0);
        }
        k_msleep(SLEEP_TIME_MS);
    }

    return 0;
}