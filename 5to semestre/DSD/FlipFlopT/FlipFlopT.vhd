-------------------------------------------------------------------------------
--
-- Title       : puertos
-- Design      : FlipFlopT
-- Author      : egonzalezb1600@alumno.ipn.mx
-- Company     : IPN
--
-------------------------------------------------------------------------------
--
-- File        : c:\My_Designs\FlipFlopT\FlipFlopT\src\FlipFlopT.vhd
-- Generated   : Tue Nov 23 16:46:35 2021
-- From        : interface description file
-- By          : Itf2Vhdl ver. 1.22
--
-------------------------------------------------------------------------------
--
-- Description : 
--
-------------------------------------------------------------------------------

--{{ Section below this comment is automatically maintained
--   and may be overwritten
--{entity {puertos} architecture {FFT}}

library IEEE;
use IEEE.std_logic_1164.all;

entity puertos is
	 port(
		 T : in STD_LOGIC;
		 Clock : in STD_LOGIC;
		 Q : out STD_LOGIC
	     );
end puertos;

--}} End of automatically maintained section

architecture FFT of puertos is
signal tmp: std_logic;
begin
process (Clock)
begin
if Clock'event and Clock='1' then
if T='0' then
tmp <= tmp;
elsif T='1' then
tmp <= not (tmp);
end if;
end if;
end process;
Q <= tmp;
end FFT;
