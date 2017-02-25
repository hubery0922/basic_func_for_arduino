#ifndef basic_func_for_arduino_h
#define basic_func_for_arduino_h

int Send(String str);    //二进制发送数据字符串到Serial 
String recv();     //读取本地串口数据返回读取的字符串
int EEPROM_read();  //连续读取 EEPROM 中2个字节(每个字节0-255)然后组成的 一个数(0-1023) 返回
void EEPROM_read_Set_parameters();   //读取 EEPROM 中的设置参数
void EEPROM_write();  //写入 EEPROM 地址0-1 两个字节  范围0-1023之间的值   
void EEPROM_write_Set_parameters();  //将不同传感器设置的模式参数保存到EEPROM中， 写入 EEPROM 地址2-14 13个字节  范围0-1023之间的值   
String Current_time(); // 该函数返回当前时刻   如:  "2015-8-18 11:8:00"
String  Decoding(String str);//该函数可以解析字符串输出