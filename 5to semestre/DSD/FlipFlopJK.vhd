-------------------------------------------------------------------------------
--
-- Title       : FlipFlopJK
-- Design      : FFD
-- Author      : Sergi
-- Company     : Instituto Politécnico Nacional
--
-------------------------------------------------------------------------------
--
-- File        : c:\My_Designs\FlipFlops\FFD\src\FlipFlopJK.vhd
-- Generated   : Tue Sep 21 22:31:18 2021
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
--{entity {FlipFlopJK} architecture {FlipFlopJK}}

library IEEE;
use IEEE.std_logic_1164.all;

entity FlipFlopJK is
	 port(
		 J : in STD_LOGIC;
		 K : in STD_LOGIC;
		 CLK : in STD_LOGIC;
		 Q : out STD_LOGIC;
		 Qn : out STD_LOGIC
	     );
end FlipFlopJK;

--}} End of automatically maintained section

architecture FlipFlopJK of FlipFlopJK is	 
	signal aux : std_logic;
begin

	process(CLK)
	begin
		if(CLK'event and CLK = '1')
		then
			aux <= (J and not aux) or (not K and aux);  
		end if;
	end process;
	
	Q <= aux;
	
	Qn <= not aux;
	
end FlipFlopJK;
