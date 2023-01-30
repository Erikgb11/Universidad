
--  CYPRESS NOVA XVL Structural Architecture

--  JED2VHD Reverse Assembler - 6.3 IR 35


--    VHDL File: alu4bits.vhd

--    Date: Sat Apr 09 11:19:42 2022

--  Disassembly from Jedec file for: c22v10

--  Device Ordercode is: PALCE22V10-25PC/PI
library ieee;
use ieee.std_logic_1164.all;

library primitive;
use primitive.primitive.all;


-- Beginning Test Bench Header

ENTITY ula IS
    PORT (
	                   a :    in std_logic_vector (3 downto 0) ;
	                   b :    in std_logic_vector (3 downto 0) ;
	                   o : inout std_logic_vector (3 downto 0) ;
	                 sel :    in std_logic_vector (2 downto 0)
    );
END ula;

-- End of Test Bench Header

ARCHITECTURE DSMB of ula is

	signal jed_node1	: std_logic:='0' ; -- b(3)
	signal jed_node2	: std_logic:='0' ; -- b(2)
	signal jed_node3	: std_logic:='0' ; -- b(1)
	signal jed_node4	: std_logic:='0' ; -- a(2)
	signal jed_node5	: std_logic:='0' ; -- sel(2)
	signal jed_node6	: std_logic:='0' ; -- sel(1)
	signal jed_node7	: std_logic:='0' ; -- sel(0)
	signal jed_node8	: std_logic:='0' ; -- b(0)
	signal jed_node9	: std_logic:='0' ; -- a(3)
	signal jed_node10	: std_logic:='0' ; -- a(1)
	signal jed_node11	: std_logic:='0' ; -- a(0)
	signal jed_node12	: std_logic:='0' ;
	signal jed_node13	: std_logic:='0' ;
	signal jed_node14	: std_logic:='0' ;
	signal jed_node17	: std_logic:='0' ;
	signal jed_node18	: std_logic:='0' ;
	signal jed_node19	: std_logic:='0' ;
	signal jed_node20	: std_logic:='0' ;
	signal jed_node23	: std_logic:='0' ;
	signal jed_node24	: std_logic:='0' ;

	for all: c22v10m use entity primitive.c22v10m (sim);

SIGNAL  one:std_logic:='1';
SIGNAL  zero:std_logic:='0';
SIGNAL  jed_oept_1:std_logic:='0';
--Attribute PIN_NUMBERS of b(3):SIGNAL is "0001";

SIGNAL  jed_oept_2:std_logic:='0';
--Attribute PIN_NUMBERS of b(2):SIGNAL is "0002";

SIGNAL  jed_oept_3:std_logic:='0';
--Attribute PIN_NUMBERS of b(1):SIGNAL is "0003";

SIGNAL  jed_oept_4:std_logic:='0';
--Attribute PIN_NUMBERS of a(2):SIGNAL is "0004";

SIGNAL  jed_oept_5:std_logic:='0';
--Attribute PIN_NUMBERS of sel(2):SIGNAL is "0005";

SIGNAL  jed_oept_6:std_logic:='0';
--Attribute PIN_NUMBERS of sel(1):SIGNAL is "0006";

SIGNAL  jed_oept_7:std_logic:='0';
--Attribute PIN_NUMBERS of sel(0):SIGNAL is "0007";

SIGNAL  jed_oept_8:std_logic:='0';
--Attribute PIN_NUMBERS of b(0):SIGNAL is "0008";

SIGNAL  jed_oept_9:std_logic:='0';
--Attribute PIN_NUMBERS of a(3):SIGNAL is "0009";

SIGNAL  jed_oept_10:std_logic:='0';
--Attribute PIN_NUMBERS of a(1):SIGNAL is "0010";

SIGNAL  jed_oept_11:std_logic:='0';
--Attribute PIN_NUMBERS of a(0):SIGNAL is "0011";

SIGNAL  jed_oept_15:std_logic:='0';
SIGNAL  jed_sum_15,jed_fb_15:std_logic:='0';
--Attribute PIN_NUMBERS of o(3):SIGNAL is "0015";

SIGNAL  jed_oept_16:std_logic:='0';
SIGNAL  jed_sum_16,jed_fb_16:std_logic:='0';
--Attribute PIN_NUMBERS of o(1):SIGNAL is "0016";

SIGNAL  jed_oept_21:std_logic:='0';
SIGNAL  jed_sum_21,jed_fb_21:std_logic:='0';
--Attribute PIN_NUMBERS of o(0):SIGNAL is "0021";

SIGNAL  jed_oept_22:std_logic:='0';
SIGNAL  jed_sum_22,jed_fb_22:std_logic:='0';
--Attribute PIN_NUMBERS of o(2):SIGNAL is "0022";

SIGNAL  jed_oept_25:std_logic:='0';
SIGNAL  jed_node25,jed_sum_25:std_logic:='0';
SIGNAL  jed_oept_26:std_logic:='0';
SIGNAL  jed_node26,jed_sum_26:std_logic:='0';

BEGIN
jed_node1 <= b(3) ;
jed_node2 <= b(2) ;
jed_node3 <= b(1) ;
jed_node4 <= a(2) ;
jed_node5 <= sel(2) ;
jed_node6 <= sel(1) ;
jed_node7 <= sel(0) ;
jed_node8 <= b(0) ;
jed_node9 <= a(3) ;
jed_node10 <= a(1) ;
jed_node11 <= a(0) ;
Mcell_15:c22v10m
generic map(comb,
   ninv,
   xpin,
   	25 ns, --tpd
	25 ns, --tea
	25 ns, --ter
	15 ns, --tco
	18 ns, --ts
	0 ns, --th
	14 ns, --twh
	14 ns, --twl
	13 ns, --tcf
	25 ns, --taw
	25 ns, --tar
	25 ns, --tap
	25 ns  --tspr
)
port map(
     d=>jed_sum_15,
     clk=>jed_node1,
     oe=>jed_oept_15,
     ss=>jed_sum_26,
     ar=>jed_sum_25,
     y=>o(3),
     fb=>jed_fb_15
   );

Mcell_16:c22v10m
generic map(comb,
   ninv,
   xpin,
   	25 ns, --tpd
	25 ns, --tea
	25 ns, --ter
	15 ns, --tco
	18 ns, --ts
	0 ns, --th
	14 ns, --twh
	14 ns, --twl
	13 ns, --tcf
	25 ns, --taw
	25 ns, --tar
	25 ns, --tap
	25 ns  --tspr
)
port map(
     d=>jed_sum_16,
     clk=>jed_node1,
     oe=>jed_oept_16,
     ss=>jed_sum_26,
     ar=>jed_sum_25,
     y=>o(1),
     fb=>jed_fb_16
   );

Mcell_21:c22v10m
generic map(comb,
   ninv,
   xpin,
   	25 ns, --tpd
	25 ns, --tea
	25 ns, --ter
	15 ns, --tco
	18 ns, --ts
	0 ns, --th
	14 ns, --twh
	14 ns, --twl
	13 ns, --tcf
	25 ns, --taw
	25 ns, --tar
	25 ns, --tap
	25 ns  --tspr
)
port map(
     d=>jed_sum_21,
     clk=>jed_node1,
     oe=>jed_oept_21,
     ss=>jed_sum_26,
     ar=>jed_sum_25,
     y=>o(0),
     fb=>jed_fb_21
   );

Mcell_22:c22v10m
generic map(comb,
   ninv,
   xpin,
   	25 ns, --tpd
	25 ns, --tea
	25 ns, --ter
	15 ns, --tco
	18 ns, --ts
	0 ns, --th
	14 ns, --twh
	14 ns, --twl
	13 ns, --tcf
	25 ns, --taw
	25 ns, --tar
	25 ns, --tap
	25 ns  --tspr
)
port map(
     d=>jed_sum_22,
     clk=>jed_node1,
     oe=>jed_oept_22,
     ss=>jed_sum_26,
     ar=>jed_sum_25,
     y=>o(2),
     fb=>jed_fb_22
   );

jed_node25<=jed_sum_25;
jed_node26<=jed_sum_26;
jed_oept_15<=(one);

jed_sum_15<= ((not(jed_node1) and not(jed_node5) and not(jed_node6)
 and not(jed_node7) and not(jed_node9)) or
((jed_node1) and (jed_node6) and (jed_node7) and (jed_node9)
) or
(not(jed_node1) and (jed_node5) and (jed_node6) and not(jed_node9)
) or
((jed_node1) and (jed_node5) and not(jed_node7) and not(jed_node9)
) or
(not(jed_node1) and (jed_node5) and not(jed_node7) and (jed_node9)
) or
((jed_node4) and (jed_node5) and not(jed_node6) and (jed_node7)
) or
((jed_node1) and not(jed_node5) and (jed_node6) and (jed_node7)
) or
(not(jed_node5) and (jed_node6) and (jed_node7) and (jed_node9)
) or
((jed_node1) and not(jed_node5) and (jed_node6) and (jed_node9)
) or
(not(jed_node5) and not(jed_node6) and (jed_node7) and (jed_node11)
));

jed_oept_16<=(one);

jed_sum_16<= ((not(jed_node3) and not(jed_node5) and not(jed_node6)
 and not(jed_node7) and not(jed_node10)) or
((jed_node3) and (jed_node6) and (jed_node7) and (jed_node10)
) or
(not(jed_node3) and (jed_node5) and (jed_node6) and not(jed_node10)
) or
((jed_node3) and (jed_node5) and not(jed_node7) and not(jed_node10)
) or
(not(jed_node3) and (jed_node5) and not(jed_node7) and (jed_node10)
) or
((jed_node5) and not(jed_node6) and (jed_node7) and (jed_node11)
) or
((jed_node3) and not(jed_node5) and (jed_node6) and (jed_node7)
) or
(not(jed_node5) and (jed_node6) and (jed_node7) and (jed_node10)
) or
((jed_node3) and not(jed_node5) and (jed_node6) and (jed_node10)
) or
((jed_node4) and not(jed_node5) and not(jed_node6) and (jed_node7)
));

jed_oept_21<=(one);

jed_sum_21<= ((not(jed_node5) and not(jed_node6) and not(jed_node7)
 and not(jed_node8) and not(jed_node11)) or
((jed_node6) and (jed_node7) and (jed_node8) and (jed_node11)
) or
((jed_node5) and (jed_node6) and not(jed_node8) and not(jed_node11)
) or
((jed_node5) and not(jed_node7) and (jed_node8) and not(jed_node11)
) or
((jed_node5) and not(jed_node7) and not(jed_node8) and (jed_node11)
) or
((jed_node5) and not(jed_node6) and (jed_node7) and (jed_node9)
) or
(not(jed_node5) and (jed_node6) and (jed_node7) and (jed_node8)
) or
(not(jed_node5) and (jed_node6) and (jed_node7) and (jed_node11)
) or
(not(jed_node5) and (jed_node6) and (jed_node8) and (jed_node11)
) or
(not(jed_node5) and not(jed_node6) and (jed_node7) and (jed_node10)
));

jed_oept_22<=(one);

jed_sum_22<= ((not(jed_node2) and not(jed_node4) and not(jed_node5)
 and not(jed_node6) and not(jed_node7)) or
((jed_node2) and (jed_node4) and (jed_node6) and (jed_node7)
) or
(not(jed_node2) and not(jed_node4) and (jed_node5) and (jed_node6)
) or
((jed_node2) and not(jed_node4) and (jed_node5) and not(jed_node7)
) or
(not(jed_node2) and (jed_node4) and (jed_node5) and not(jed_node7)
) or
((jed_node5) and not(jed_node6) and (jed_node7) and (jed_node10)
) or
((jed_node2) and not(jed_node5) and (jed_node6) and (jed_node7)
) or
((jed_node4) and not(jed_node5) and (jed_node6) and (jed_node7)
) or
((jed_node2) and (jed_node4) and not(jed_node5) and (jed_node6)
) or
(not(jed_node5) and not(jed_node6) and (jed_node7) and (jed_node9)
));

end DSMB;
