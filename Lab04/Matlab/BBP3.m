A=importdata('SSP_Tests_Timed_PD_P3.dat');
%A = table2array(A);
N_P3 = A(:,1)
Tempo_P3 = A(:,2)
%%
A=importdata('SSP_Tests_Timed_PD_P4.dat');

N_P4 = A(:,1)
Tempo_P4 = A(:,2)
%%
A=importdata('SSP_Tests_Timed_PD_P5.dat');

N_P5 = A(:,1)
Tempo_P5 = A(:,2)
%%
A=importdata('SSP_Tests_Timed_PD_Rand.dat');

N_Rand = A(:,1)
Tempo_Rand = A(:,2)
%%
A=importdata('SSP_Tests_Timed_PD_AVIS.dat');

N_AVIS = A(:,1)
Tempo_AVIS = A(:,2)
%%
A=importdata('SSP_Tests_Timed_PD_EVOD.dat');

N_EVOD = A(:,1)
Tempo_EVOD = A(:,2)