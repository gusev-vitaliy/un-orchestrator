This network function implements a DPI on packets coming from its first interface.
It works with two interfaces, and implements a bridge between them.

By default, it drops the HTTP containing the words "porn" and "sex". You can
add other words by exiting the file "runtime.c"

===============================================================================

Reqiured libraries:

* DPDK  
     git clone https://github.com/bisdn/dpdk-dev
     
* libpcre  
    apt-get install libpcre3 libpcre3-dev

===============================================================================

Compile it as follows:
* export RTE_SDK=absolute_path_dpdk  
  (e.g., export RTE_SDK=~/Desktop/dpdk-dev)  
* make

===============================================================================

* If you are going to use this network function together with the un-orchestrator, 
you can skip this part *

Usage:  
 sudo ./dpi -c core_mask -n memory_channels --proc-type=secondary -- 
                --p port_name --p port_name --s semaphore_name --l file_name                                          
                                                                                         
Parameters:  
  -c core_mask  
        Number of lcores used by the NFs. Note that currently only one lcore is
        actually used.                                                                              
  -n memory_channels  
        Number of channels used by the NFs to access to the memory.                      
  --proc-type=secondary  
        The NF must be executed as a DPDK secondary process.                             
  --p port_name  
	    Name of a port of the NF. This parameter must be repeated two times, 
	    since this NF requires two ports.  
  --l file_name  
        Name of the file used to log information.                                        
                                                                                         
Options:   
  --s semaphore_name [mandatory if the NF is compiled with the flag ENABLE_SEMAPHORE]  
        Name of the semaphore to be used by the NF.                                                                                    
  --h   Print the help.
                                                                                         
Example:  
  sudo ./url_filter -c 0x1 -n 2 --proc-type=secondary -- --p port1 --p port2 --s sem

