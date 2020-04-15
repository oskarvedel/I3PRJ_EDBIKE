/** @file xxx.xxx
 *  @brief kort beskrivelse (på én linje)
 * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
 * lang beskrivelse, lang beskrivelse
 *  @author forfatter1
 *  @author forfatter2
 *  @bug Ingen kendte bugs
 */

#include "SPI.hpp"

SPI::SPI(int deviceNumber, unsigned char bitsPerWord, unsigned int speed):
deviceNumber_(deviceNumber),bitsPerWord_(bitsPerWord),speed_(speed)
{
    

    /************************opening node in /dev/ ************************/
    if(deviceNumber==0)								
	{
		fileDescriptor_=open("/dev/spidev0.0",O_RDWR);		//open device zero.
	}
	else if (deviceNumber==1)
	{
		fileDescriptor_=open("/dev/spidev0.1",O_RDWR);		//open device one.
	}
	if(fileDescriptor_<0)
	{
		std::cout<<std::endl<<"Error opening dev/spidev"<<std::endl;
	}

	

	/*******************************config********************************/
	if((ioctl(fileDescriptor_,SPI_IOC_WR_MODE,&spiMode_))<0)											        
	{
		std::cout<<std::endl<<"Error setting write mode."<<std::endl;
		close(fileDescriptor_);
		//exit(1);
	}
			
	if((ioctl(fileDescriptor_,SPI_IOC_RD_MODE,&spiMode_))<0)
	{
		std::cout<<std::endl<<"Error setting read mode."<<std::endl;
		close(fileDescriptor_);
		//exit(1);
	}
	
	if((ioctl(fileDescriptor_, SPI_IOC_WR_BITS_PER_WORD, &bitsPerWord_))<0)
	{
		std::cout<<std::endl<<"Error setting bits per word for write."<<std::endl;
		close(fileDescriptor_);
		//exit(1);
	}
	
	if((ioctl(fileDescriptor_, SPI_IOC_RD_BITS_PER_WORD, &bitsPerWord_))<0)
	{
		std::cout<<std::endl<<"Error setting bits per word for read."<<std::endl;
		close(fileDescriptor_);
		//exit(1);
	}
	
	if((ioctl(fileDescriptor_,SPI_IOC_WR_MAX_SPEED_HZ, &speed_))<0)
	{
		std::cout<<std::endl<<"Error setting speed for write."<<std::endl;
		close(fileDescriptor_);
		//exit(1);
	}
	
	if((ioctl(fileDescriptor_,SPI_IOC_RD_MAX_SPEED_HZ, &speed_))<0)
	{
		std::cout<<std::endl<<"Error setting speed for read."<<std::endl;
		close(fileDescriptor_);
		//exit(1);
	}
	//ioctlfileDescriptor_,SPI_IOC_RD_LSB_FIRST,<insert 1 to make true>);	//Defaults to MSB FIRST
	//ioctlfileDescriptor_,SPI_IOC_WR_LSB_FIRST,<insert 1 to make true>);	//Defaults to MSB FIRST
}


SPI::~SPI()
{
	if((close(fileDescriptor_))<0)
	{
		std::cout<<std::endl<<"Error closing node."<<std::endl;
		////exit(1);
	}
}


int SPI::readAndWrite(int messageLen, int csAfterTransfer)
{
	memset(message_, 0, sizeof(message_));
	
    for (int i = 0; i < messageLen; i++)
	{
		message_[i].tx_buf=(unsigned long)&txBuffer_[i];
		message_[i].rx_buf=(unsigned long)&rxBuffer_[i];
		message_[i].len=1;
		message_[i].cs_change=csAfterTransfer;
		//message_[i].delay_usecs=1000;
	}
	
	if((ioctl(fileDescriptor_,SPI_IOC_MESSAGE(messageLen),message_))<0)
	{
		//std::cout<<std::endl<<"Transfer error."<<std::endl;
		close(fileDescriptor_);
		return false;
	}
	return true;
}


void SPI::getValueOfRxBuffer(uint8_t* callBackBuffer)
{
	for (size_t i = 0; i < maxMessageLength; i++)
	{
		callBackBuffer[i]=rxBuffer_[i];
	}
}

void SPI::setValueOfTxBuffer(std::string tx)
{
	for (size_t i = 0; i < maxMessageLength; i++)
	{
		txBuffer_[i]=tx[i];
	}
}

void SPI::setValueOfTxBuffer(uint8_t forIndex0,uint8_t forIndex1,
                                    uint8_t forIndex2, uint8_t forIndex3)
{
	txBuffer_[0]=forIndex0;
	txBuffer_[1]=forIndex1;
	txBuffer_[2]=forIndex2;
	txBuffer_[3]=forIndex3;
}

void SPI::printRxToScreen()
{
	//std::cout<<"rxIndex 0: "<< (int)rxBuffer_[0]<<std::endl;
	//std::cout<<"rxIndex 1: "<< (int)rxBuffer_[1]<<std::endl;
	//std::cout<<"rxIndex 2: "<< (int)rxBuffer_[2]<<std::endl;
	//std::cout<<"rxIndex 3: "<< (int)rxBuffer_[3]<<std::endl;
}

void SPI::printTxToScreen()
{
	std::cout<<"txIndex 0: "<< (int)txBuffer_[0]<<std::endl;
	std::cout<<"txIndex 1: "<< (int)txBuffer_[1]<<std::endl;
	std::cout<<"txIndex 2: "<< (int)txBuffer_[2]<<std::endl;
	std::cout<<"txIndex 3: "<< (int)txBuffer_[3]<<std::endl;
}
