library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

entity ULA is port(
A,B	:	in		std_logic_vector(3 downto 0);
O		:	out	std_logic_vector(3 downto 0);
sel	:	in		std_logic_vector(2 downto 0)	
);
end ULA;

Architecture hardware of ULA is
begin
process(A,B, sel)
begin

	case sel is
		when "000"	=>	O	<=	A	  NOR 	  B;
		when "001"	=>O(0) <= A(1);
					  O(1) <= A(2);
					  O(2) <= A(3);
					  O(3) <= A(0);		
		when "010"	=>	O	<=	A	  AND	  B;
		when "011"	=>	O	<=	A	  OR	  B;
		when "100"	=>	O	<=	A	  XOR	  B;
		when "101"	=>O(0) <= A(3);
					  O(1) <= A(0);
					  O(2) <= A(1);
					  O(3) <= A(2);	
		when "110"	=>	O	<=	A	  NAND	  B;
		when others =>	O	<=	A	  XNOR	  B;
	end case;
end process;
end hardware;