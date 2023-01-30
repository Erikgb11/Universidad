-------------------------------------------------------------------------------
--
-- Title       : puertos
-- Design      : FFD
-- Author      : Sergi
-- Company     : Instituto Politécnico Nacional
--
-------------------------------------------------------------------------------
--
-- File        : c:\My_Designs\FlipFlops\FFD\src\FlipFlopSR.vhd
-- Generated   : Wed Sep 22 16:32:23 2021
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
--{entity {puertos} architecture {FFSR}}

library IEEE;
use IEEE.std_logic_1164.all;

entity puertos is
	 port(
		 S : in STD_LOGIC;
		 R : in STD_LOGIC;
		 Q : out STD_LOGIC;
		 Qn : out STD_LOGIC
	     );
end puertos;							  

architecture FFSR of puertos is	 
signal aux : std_logic;
signal aux_n : std_logic;
begin

Q <= aux;
Qn <= aux_n;

aux <= R nor aux_n;
aux_n <= S nor aux;

end FFSR;
