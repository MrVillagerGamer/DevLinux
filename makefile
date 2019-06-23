GCCARGS = -m32 -fno-stack-protector
ASMARGS = -felf32
LNKARGS = -melf_i386

OBJECTS = obj/kernel.o obj/loader.o obj/idt.o \
          obj/idts.o obj/port.o obj/vga.o \
		  obj/ps2.o obj/rtc.o obj/ide.o \
		  obj/fat.o obj/pci.o obj/hd.o

obj/%.o: src/%.c
	gcc $(GCCARGS) -Iinc -c -o $@ $<

obj/%.o: src/%.asm
	nasm $(ASMARGS) -o $@ $<
	
kernel.iso: linker.ld $(OBJECTS)
	ld $(LNKARGS) -T $< -o bin/iso/boot/kernel.bin $(OBJECTS)
	grub-mkrescue bin/iso -o $@
	
clean:
	rm -r obj
	mkdir obj