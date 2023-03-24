#include <xinu.h>

uint16 min(uint16 first, uint16 second) {
    return first < second ? first : second;
}