# Paper Quantity Calculator

This project is the partial codes for **2019 National Undergraduate Electronic Design Contest(NUEDC) F**. 

[中文版本](https://github.com/Kexin-Tang/Paper-Quantity-Calculator)
-----
# Requirement

You can *only use* two 5cm×5cm boards for testing paper, and there are no other items except wires.

Also, the time is limited in *4 days*.

-----
# Picture

![FDC2214_circuit.png](https://i.loli.net/2020/09/11/13sCkpVu4Dczvt8.png)
-----
# File Structure

File name   |  Function
:----:|:------:
main.c | Define the main page
touch  | Achieve UI pages, touch detection and other LCD functions
lcd    | IIC, register initialization, etc.
fdc2214| Capacity sensor controlling

### Note
* If using FPGA, please set ip module and program Verilog HDL in hardware layers
* If using MCU, please pay attention to the TIMER and other peripherals.
