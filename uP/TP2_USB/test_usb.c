#include <stdio.h>
#include <usb.h>
#include <stdint.h>

struct usb_device * dev = NULL;
usb_dev_handle * dev_handle = NULL;

void initialize(void) {
	struct usb_bus * busses = NULL;
	int nb = 0;
	
	usb_init();
	
	nb = usb_find_busses();
	printf("J'ai trouve %d USB\n", nb);

	nb = usb_find_devices();
	printf("J'ai trouve %d devices\n", nb);

	busses = usb_get_busses();
	
	while (busses != NULL) {
		printf("bus %s\n", busses->dirname);

		struct usb_device * devices = busses->devices;
		while (devices != NULL) {
			printf("bus %s, device %s (%04hx:%04hx)\n", busses->dirname, 
					devices->filename, 
					devices->descriptor.idVendor, 
					devices->descriptor.idProduct);
			
			if (devices->descriptor.idVendor == 0x04d8 
					&& devices->descriptor.idProduct == 0x000c) {
				dev = devices;
				return;
			}
			
			devices = devices->next;
		}
		
		busses = busses->next;
	}

	printf("Carte Microchip non connectee !\n");
	exit(1);
}

void open_device(void) {
	int ret = 0;
	
	dev_handle = usb_open(dev);
	if (dev_handle == NULL) {
		printf("usb_open: %s\n", usb_strerror());
		exit(1);
	}
	
	ret = usb_reset(dev_handle);
	if (ret != 0) {
		printf("usb_reset: %s\n", usb_strerror());
		exit(1);
	}

/*	ret = usb_resetep(dev_handle, 0x01);
	if (ret != 0) {
		printf("usb_resetep: %s\n", usb_strerror());
		exit(1);
	}*/
	
}

void close_device(void) {
	int ret = usb_close(dev_handle);

	if (ret != 0) {
		printf("usb_close: %s\n", usb_strerror());
	}
}

void play_with_leds(void) {
	char usb_data[3];
	int ret = 0;
	
	usb_data[0] = 0x32;
	int n = 3;
	int e = 1;

	while (1) {
		usb_data[1] = n;
		usb_data[2] = e;
	
		printf("LED = %d, etat = %d\n", n, e);
		
		ret = usb_interrupt_write(dev_handle, 0x01, usb_data, 3, 20);
		if (ret != 3) {
			printf("usb_interrupt_write: ret = %d: %s\n", ret, usb_strerror());
			exit(1);
		}

		if (n == 3) {
			n = 4;
		} else {
			n = 3;
			e = !e;
		}
		
		sleep(1);
	}
}

void read_pot(void) {
	char usb_in[3];
	char usb_out[1];
	int ret;

	usb_out[0] = 0x37;

	while (1) {
		ret = usb_interrupt_write(dev_handle, 0x01, usb_out, 1, 50);
		if (ret != 1) {
			printf("usb_interrupt_write: ret = %d: %s\n", ret, usb_strerror());
			exit(1);
		}
	
		ret = usb_interrupt_read(dev_handle, 0x81, usb_in, 3, 50);
		if (ret != 3) {
			printf("usb_interrupt_write: ret = %d: %s\n", ret, usb_strerror());
			exit(1);
		}
	
		printf("pot = {0x%02hhx, 0x%02hhx, 0x%02hhx}\n", usb_in[0], usb_in[1], usb_in[2]);
		sleep(1);
	}
}

void read_temp(void) {
	char usb_in[3];
	char usb_out[1];
	int ret;
	uint16_t * temp;
	char temp_2[2];

	usb_out[0] = 0x34;

	while (1) {
		ret = usb_interrupt_write(dev_handle, 0x01, usb_out, 1, 50);
		if (ret != 1) {
			printf("usb_interrupt_write: ret = %d: %s\n", ret, usb_strerror());
			exit(1);
		}
	
		ret = usb_interrupt_read(dev_handle, 0x81, usb_in, 3, 50);
		if (ret != 3) {
			printf("usb_interrupt_write: ret = %d: %s\n", ret, usb_strerror());
			exit(1);
		}

		temp_2[0] = usb_in[2];
		temp_2[1] = usb_in[1];
		temp = temp_2;

		
		USB_LE16_TO_CPU(*temp);
		
		*temp >>= 3;
		*temp = (*temp * 10) >> 4;

		
		printf("temp = %hd°\n", *temp);

		printf("temp = {0x%02hhx, 0x%02hhx, 0x%02hhx}\n", usb_in[0], usb_in[1], usb_in[2]);
		
		sleep(1);
	}
}

int main(int argc, char ** argv) {
	initialize();
	open_device();

//	play_with_leds();
//	read_pot();
	read_temp();
	
	close_device();

	return 0;
}

