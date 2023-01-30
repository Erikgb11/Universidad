-------------------------------------------------------------------------------
--
-- Title       : puertos
-- Design      : FFD
-- Author      : Sergi
-- Company     : Instituto Politécnico Nacional
--
-------------------------------------------------------------------------------
--
-- File        : c:\My_Designs\FlipFlops\FFD\src\FlipFlopD.vhd
-- Generated   : Mon Sep 20 22:26:17 2021
-- From        : interface description file
-- By          : Itf2Vhdl ver. 1.22
--
-------------------------------------------------------------------------------
--
-- Description : A program for a Flip Flop D
--
-------------------------------------------------------------------------------

--{{ Section below this comment is automatically maintained
--   and may be overwritten
--{entity {puertos} architecture {FFD}}

library IEEE;
use IEEE.std_logic_1164.all;

entity puertos is
	 port(
		 D : in STD_LOGIC;
		 CLK : in STD_LOGIC;
		 Q : out STD_LOGIC;
		 Qn : out STD_LOGIC
	     );
end puertos;

--}} End of automatically maintained section

architecture FFD of puertos is
begin
	
	Process(CLK)
	begin
		if(CLK'event and CLK = '1')
		then
			Q <= D;	
			
			Qn <= not D;
		end if;
	end Process;

end FFD;
