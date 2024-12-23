#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

const int VGA_COLS = 80;
const int VGA_ROWS = 25;

int term_col = 0;
int term_row = 0;

uint8_t term_colour = 0x0F;

void term_init() {

    for(int col = 0; col < VGA_COLS; col++) {

        for(int row = 0; row < VGA_ROWS; row++){

            const size_t index = (VGA_COLS * row) + col;

            vga_buffer[index] = ((uint16_t)term_colour << 8) | ' ' ;
        }
    }
}

void kputc(char c) {

    switch(c){

        case '\n': {
          term_col = 0;
          term_row++;
          break;
        }

        case '\t': {
            term_col= 0;
            term_row = 4;
            break;
        }

        case '\v': {
            term_col = 4;
            term_row = 0;
            break;
        }

        default: {
            const size_t index = (VGA_COLS * term_row) + term_col;

            vga_buffer[index] = ((uint16_t)term_colour << 8) | c ;
            term_col++;
            break;

        }

    }
    if(term_col >= VGA_COLS){
        term_col = 0;
        term_row ++;
    }

    if(term_row >= VGA_ROWS) {
        term_col = 0;
        term_row = 0;
    }
}

void kprintf(const char* str) {

    for (size_t i = 0; str[i] != '\0'; i++)
        kputc(str[i]);

}

void krl_main() {


    kprintf("\v Freekx");
}
