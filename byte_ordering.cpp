#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstddef>

using byte_pointer = unsigned char *;

void show_bytes(byte_pointer p, std::size_t size) {
	for (int i = 0; i != size; ++i) {
		std::printf(" %.2x", p[i]);
	}
	std::printf("\n");
}

void show_int(int val) {
	show_bytes(reinterpret_cast<byte_pointer>(&val), sizeof(int));
}

void show_float(float f) {
	show_bytes(reinterpret_cast<byte_pointer>(&f), sizeof(float));
}

void show_pointer(void *x) {
	show_bytes(reinterpret_cast<byte_pointer>(&x), sizeof(void *));
}

void test_show_bytes(int val) {
	int ival = val;
	float fval = static_cast<float>(ival);
	int *pval = &ival;

	show_int(ival);
	show_float(fval);
	show_pointer(pval);
}

int main() {
	int val = 0;
	std::scanf("%d", &val);

	test_show_bytes(val);

	return 0;
}
