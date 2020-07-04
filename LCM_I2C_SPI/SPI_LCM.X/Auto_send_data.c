unsigned char xlabel_length=0;  // using this part at main for user define the xlabel length in the for loop
unsigned char ylabel_length=0; //  using this part at main for user define the ylabel length in the for loop

unsigned char xlabel=0;  //user define in data A5-A0
unsigned char ylabel=0; //user define in data D0-D3
unsigned char data1;  //A5-A0
unsigned char data2; //D0-D3


unsigned char sentdata(unsigned char slave_address,unsigned int data1,unsigned int data2,unsigned char bit)
{
    unsigned char databuff[40]={0};// Martix for the data user input
    unsigned char slave_length=3;//command 100 101 110

    //check if the bit is data or is inital
    if (bit==10) //consider bit 10 is data auto send for user
    {
        for(xlabel=data1;xlabel<=xlabel_length;xlabel++)
        {
	        reg=data1;			//user data into register
	        reg=reg<<4;			//shift register 4 time to part the left part D0-D3
	        reg=(reg|data2);	//stick the last D0-D3 into register
	
	        if(xlabel==31)		//for loop count if xlabel is max
	        {
		        ylabel++;		//if xlabel count to max vaule than ylabel puls one
		        data2=ylabel;	//
		        xlabel=0;		//clear this round of the xlabel vaule start next cycle
		        if(ylabel==ylabel_length)//this part is the max of the ylabel of the ylabel counting
		        {
			         ylabel=0; //clear the ylabel vaule
						
		        }
		        else         //restart the autocounting and the xlabel & ylabel set as user define vaule
		        {
			         xlabel=data1;
			         ylabel=data2;
		        }
	        }
        }   
    }
    else  //inital data deal in this part      
    {
    reg=data1;
    reg=reg<<4;
    reg=(reg|data2);
    }

    sendbit=bit+slave_length;//total length of the data

    //slave_address into databuf
    for (n = 0; n< slave_length-1; n++)
    {
        databuff[n] = (slave_address>>(slave_length-n-1) & 0x01);
    }

    //user data logic and && into martixa
    for ( n = 0; n < bit-1; n++) //data match bit and logic and & 0x01 output RC5  
    {
        databuff[n+slave_address]=((reg>>(bit-n-1))&0x01); 
    //  DataBuf[n+SlaveLength-1] = (REG2>>(Length-n)) & 0x01
    }
    //end of data in martix

    clk_control=1;
    endsend=0;
    while (sendbit!=0) // lock data for waitting send done
    {
        while((CLK_LAT==1)&&(CLK_count))
        {
            for(i=0; i<= sendbit; i++)//output part need count slave_address
            {                
                Data_LAT=databuff[i];  //test
                sendbit--;
                endsend++;
                CLKOK=0;        //send end
                while(!CLKOK)
                {
                
                }
                if(endsend==bit+slave_length)//check if data endsend counter start at 1 and counter to bit+1
                {
                    Data_LAT=0;
                    clk_control=0;
                    return(sendbit);//if sendbir not equal to zero => error
                }
            } 
        }
    }
}