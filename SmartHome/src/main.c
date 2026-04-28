#include "Fan.h"
int main(void) {
	FanInit();
	while(1){
		FanControl();
	}
	return 0;
}


