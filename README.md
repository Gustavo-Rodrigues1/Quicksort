# Quicksort
Comparação entre 2 implementações (hoare e lomuto) diferentes de quicksort com 3 metódos diferentes de seleção de pivô (lógica padrão, por mediana de 3 e por pivô aleatório), totalizando 6 formas diferentes de realizar quicksort. O código ira contar toda vez o quicksort trocar de pivô ou for chamado recursivamente e será expresso no final com do método com menor número de chamadas recursivas + trocas para o que tiver o maior número de chamadas recursivas + trocas.

# 📥 Formato do Arquivo de Entrada
O arquivo de entrada pode receber vários vetores no seguinte formato<br><br>
totalDeVetores <br>
quantidadeDeElementosDoVetor <br>
elementoDoVetor elementoDoVetor elementoDoVetor <br>
...<br>
quantidadeDeElementosDoVetor <br>
elementoDoVetor elementoDoVetor elementoDoVetor <br>
...<br><br>

(Exemplo)<br>
3<br>
4<br>
1 2 3 4<br>
2<br>
2 1<br>
5<br>
4 4 4 4 4

# 📤 Formato da Saída
As siglas representam os seguintes formas:<br>
HP: hoare padrão<br>
HA: hoare aleatório<br>
HM: hoare por mediana<br>
LP: lomuto padrão<br>
LA: lomuto aleatório<br>
LM: lomuto por mediana<br><br>
O método que tiver o menor número de chamadas recursivas + trocas tem sua sigla impressa primeiro<br><br>
númeroDoVetor:N(quantidadeDeElementosDoVetor),primeiroColocado(numeroDeChamadas+Trocas),segundoColocado(numeroDeChamadas+Trocas),terceiroColocado(numeroDeChamadas+Trocas),quartoColocado(numeroDeChamadas+Trocas),quintoColocado(numeroDeChamadas+Trocas),sextoColocado(numeroDeChamadas+Trocas)<br>
...
númeroDoVetor:N(quantidadeDeElementosDoVetor),primeiroColocado(numeroDeChamadas+Trocas),segundoColocado(numeroDeChamadas+Trocas),terceiroColocado(numeroDeChamadas+Trocas),quartoColocado(numeroDeChamadas+Trocas),quintoColocado(numeroDeChamadas+Trocas),sextoColocado(numeroDeChamadas+Trocas)<br><br>

(exemplo)<br>
0:N(1842),HP(8369),HA(10267),HM(10661),LM(14028),LP(14405),LA(17752)<br>
1:N(1039),HP(4487),HA(5615),HM(5807),LM(7148),LA(7967),LP(8170)<br>
2:N(119),HP(439),HA(552),HM(563),LP(617),LM(630),LA(703)<br>
