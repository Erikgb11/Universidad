library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

package subccts is
	COMPONENT regn--registro
		GENERIC(N:INTEGER := 8);
		PORT(R :IN std_logic_vector(N-1 downto 0);
		Rin, Clock:IN std_logic;
		Q :OUT std_logic_vector(N-1 downto 0));
	END COMPONENT;
	
	COMPONENT trin -- buffers triestado
		GENERIC(N: INTEGER := 4);
		PORT(X : IN std_logic_vector(N-1 downto 0);
		E : IN std_logic;
		F : OUT std_logic_vector(N-1 downto 0));
	END COMPONENT;
	
	COMPONENT dec2to4-- decodificador binario dos a cuatro
		PORT(w : IN std_logic_vector(1 downto 0);
		En : IN std_logic;
		y : OUT std_logic_vector(0 to 3));
	END COMPONENT;
	
	COMPONENT upcount --Contador ascendente
		PORT (Clear, Clock : IN std_logic;
		Q : BUFFER std_logic_vector(1 downto 0));
	END COMPONENT;
end subccts;