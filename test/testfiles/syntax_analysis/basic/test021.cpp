char* str = "Hello!\n";

int main(int argc, char **argv)
{
	asm("mov $4, %eax");
	asm("mov $1, %ebx");
	asm("mov str, %ecx");
	asm("mov $8, %edx");
	asm("int $0x80");

	return 0;
}
