library ieee;
use ieee.std_logic_1164.all;
entity dec2to4 is
port (A: in std_logic_vector(1 downto 0); --- Entradas de dirección
	E: in std_logic; --- Entrada de habilitación
	O: out std_logic_vector(3 downto 0)); --- Salidas
end dec2to4;
architecture DEC of dec2to4 is
begin
process (A, E)
	begin
	if E = '0' then
	   O <= "0000";
	else
		case A is
			when "00" => O <= "0001";
			when "01" => O <= "0010";
			when "10" => O <= "0100";
			when "11" => O <= "1000";
			when others => O <= "0000";
		end case;
	end if;
end process;
end DEC;