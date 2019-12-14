#include"BitWrite.h"

void BitWrite::flush() {
	out.put(buf); // thêm một kí tự  link tham khảo về 'ostream' :http://www.cplusplus.com/reference/ostream/ostream/
	out.flush(); // Bộ đệm dòng đầu ra
	buf = Tbits = 0;
}

void BitWrite::writeBit(int i)
{
	if (i == -1)     // đến bit cuối cùng nếu bộ đệm không đầy đủ vẫn còn đệm bộ đệm
	{
		flush();
	}
	if (Tbits == 8) // Nếu bộ đệm đầy (8 bit) xóa bộ đệm
	{
		flush();
	}

	// nếu int là 1, chúng ta phải đặt bit 1 vào bộ đệm
	unsigned char mask = 1;
	if (i == 1)
	{
		mask = mask << (7 - Tbits); // dịch chuyển sang trái cho tới khi lắp đầy 8 bit
		buf = buf | mask; // đối chiếu buf(1 hoặc 0) và mask(1 hoặc 0), buf được gán lại 0 nếu cả hai toán hạng đều có giá trị 0 còn lại đều trả về 1;
	}
	// nếu int là 0, chúng ta phải đặt bit 0 vào bộ đệm
	if (i == 0)
	{
		mask = mask << (7 - Tbits);
		mask = ~mask; // đảo bit 0 -> 1 hoặc ngược lại
		buf = buf & mask; // đối chiếu buf(1 hoặc 0) và mask(1 hoặc 0), buf được gán lại 1 nếu cả hai toán hạng đều có giá trị 1 còn lại đều trả về 0;
	}
	Tbits++;                   //tăng Tbits thêm 1
}