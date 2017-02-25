int Send(String str)    //二进制发送数据字符串到Serial 
{
	for( int i = 0; i < str.length(); i++) 
	{
	Serial.write(str[i]);
	}
	return 1;  
}


String recv()     //读取本地串口数据返回读取的字符串
{
	char c;
	String  s="";
	while(Serial.available())
	{
		c=Serial.read();
		s+=c;
		delay(2);
	}
	return s;
}


//*********************************************************************************************************

int EEPROM_read()  //连续读取 EEPROM 中2个字节(每个字节0-255)然后组成的 一个数(0-1023) 返回
{
	int sum=0;  //其范围从0到4,294,967,295（2 ^ 32 - 1）
	byte w[2];
	for(int i=0;i<2;i++) 
	{
		w[i] = EEPROM.read(i);
		sum+=w[i]<<(8*i);
	}
	return sum;
}


//*********************************************************************************************************


void EEPROM_read_Set_parameters()   //读取 EEPROM 中的设置参数
{
	for(int i=0;i<13;i++) select[i] = EEPROM.read(i+2); 		
}


//*********************************************************************************************************

void EEPROM_write()  //写入 EEPROM 地址0-1 两个字节  范围0-1023之间的值   
{
	long val=0;
	for(int i=0;i<1000;i++) val += analogRead(analogPin[0]);
	val/=1000;//**************************************************************************************************************用1000次统计求平均值
	//val = map(val, 0, 1023, 0, 360);  //映射成0-360的角度

	EEPROM.write(0, val%256);
	EEPROM.write(1, val/256);

	Serial.print("Successfully written EEPROM the Wind compensation value = ");
	Serial.println(val,DEC);

	Angle_compensation = EEPROM_read();//从EEPROM读入角度补偿
	
}


//*********************************************************************************************************

void EEPROM_write_Set_parameters()  //将不同传感器设置的模式参数保存到EEPROM中， 写入 EEPROM 地址2-14 13个字节  范围0-1023之间的值   
{
	for(int i=0;i<13;i++)  EEPROM.write(i+2, select[i]);	
	Serial.print("Successfully written EEPROM the Set_parameters"); 
}


String Current_time() // 该函数返回当前时刻   如:  "2015-8-18 11:8:00"
{	
	unsigned long Time_difference = ( millis() - last_Time )/1000;  //与上一次 时间同步的 秒 间隔	
	unsigned long today_seconds=hour*3600+minute*60+second + Time_difference; //今天零点开始到此刻的总秒数	
	
	if( Time_difference>0 )
	{
		//计时器没有溢出,
		//&& (today_seconds/3600<24)    并且小时数小于24，如果超过24意味着天数更新了，于是需要立刻更新时间
		return date + String(" ") + String(today_seconds/3600) + String(":") + String((today_seconds%3600)/60) + String(":") + String((today_seconds%3600)%60);
	}
	else //如果计时器不巧在50天这个周期 溢出了  我们需要 立刻重新同步时间
	{
		Time_handler();
		return "failure! Unfortunately,timeout! try it again";
	}
}

//该函数可以解析字符串输出
String  Decoding(String str)//*********************************字符串解析函数，
{
  int index1 = str.indexOf("msg:");
  int index2 = str.indexOf("---");
  return  str.substring(index1+4,index2);
}