Sistema Monitor Ecocampus
1. Sobre o projeto
O Sistema Monitor Ecocampus é uma aplicação de terminal destinada a registrar e consultar o consumo de recursos em diferentes locais de um campus. A partir dos dados armazenados em um arquivo de texto, o sistema pode consultar o consumo de um local, comparar o valor medido com um limite recomendado e apresentar informações para acompanhamento.
Nota sobre esta documentação: este README foi elaborado com base na captura de tela da execução e no arquivo consumo_campus.txt. O código-fonte da aplicação não foi fornecido; por isso, detalhes internos de implementação e regras completas de classificação ainda precisam ser confirmados.

2. Funcionalidades demonstradas
O menu principal apresenta quatro opções:
1. Analisar consumo e gerar relatório — opção destinada à análise dos dados e à geração de um relatório.
2. Consultar local por nome — permite informar o nome de um local e consultar seus dados.
3. Acrescentar novo registro ao arquivo — solicita o nome do local, o consumo medido e o limite recomendado, e registra os dados no arquivo.
4. Sair — encerra a interação com o menu.
A captura de tela demonstra as opções 3 e 2: primeiro, o cadastro do local Faculdade; em seguida, a consulta desse local.
3. Arquivo de dados
O arquivo consumo_campus.txt armazena os registros. Cada linha contém três campos, separados por espaços:
NomeDoLocal ConsumoMedido LimiteRecomendado
Exemplo:
Faculdade 2000.00 1500.00
Biblioteca 780.50 800.00
Laboratorio1 925.00 850.00
Os campos representam:
- Nome do local: identifica a área do campus.
- Consumo medido: valor de consumo registrado, em litros conforme a saída apresentada pelo programa.
- Limite recomendado: valor de referência para comparar com o consumo medido.
O arquivo enviado contém registros de locais como Biblioteca, Cantina, Laboratórios, Ginásio, Restaurante Universitário, Datacenter e Faculdade.
4. Exemplo de consulta
Na captura, o usuário escolhe a opção 2 e consulta Faculdade. A saída apresenta:
Consumo medido:     2000.00 litros
Limite recomendado: 1500.00 litros
Classificacao:      Critico
Excesso registrado: +33.33%
Como calcular o excesso percentual
A diferença entre o consumo medido e o limite recomendado é:
Excesso em litros = consumo medido - limite recomendado
Excesso em litros = 2000 - 1500 = 500 litros
Para calcular o excesso percentual em relação ao limite:
Excesso (%) = ((consumo medido - limite recomendado)
               / limite recomendado) * 100
Aplicando os valores:
Excesso (%) = ((2000 - 1500) / 1500) * 100
Excesso (%) = 33.33%
Portanto, o consumo da Faculdade está 500 litros, ou aproximadamente 33,33%, acima do limite informado.

A classificação Critico é a apresentada na demonstração. As faixas e condições que determinam essa classificação não podem ser confirmadas sem consultar o código-fonte.
5. Exemplo de cadastro
Na demonstração, a opção 3 solicita os seguintes dados:
Nome do local (sem espaços): Faculdade
Consumo em litros: 2000
Limite recomendado em litros: 1500
Depois, o programa informa que o registro foi adicionado ao arquivo consumo_campus.txt.

A mensagem indica que o programa grava os dados no arquivo de texto para que possam ser consultados posteriormente. A implementação exata da gravação precisa ser verificada no código-fonte.
6. Fluxo de utilização
1. O programa apresenta o menu.
2. O usuário escolhe uma opção.
3. Na consulta, informa o nome do local desejado.
4. Na inclusão, informa nome, consumo e limite recomendado.
5. O programa exibe o resultado da operação.
6. O usuário pode voltar ao menu e escolher outra opção ou sair.
7. Tecnologias e conceitos observáveis
Com base nos arquivos fornecidos, é possível identificar o uso de:
- Interface de terminal: interação por mensagens de texto e opções numéricas.
- Arquivo de texto: armazenamento dos registros em consumo_campus.txt.
- Entrada de dados: coleta do nome, do consumo e do limite.
- Consulta de registros: localização de um local pelo nome.
- Cálculo percentual: comparação entre consumo medido e limite recomendado.
- Formatação de saída: apresentação dos valores com duas casas decimais.
A linguagem de programação e as bibliotecas utilizadas não podem ser comprovadas apenas pela captura e pelo arquivo de dados, embora a aparência da execução seja compatível com um programa de terminal.
8. Possíveis melhorias futuras
Estas são sugestões, não funcionalidades confirmadas na versão demonstrada:
- Validar entradas numéricas e impedir valores inválidos.
- Tratar locais inexistentes e registros duplicados.
- Permitir nomes de locais com espaços.
- Definir e documentar as faixas de classificação do consumo.
- Gerar um relatório geral com todos os locais acima do limite.
- Ordenar os locais por percentual de excesso.
- Adicionar testes para os cálculos e para leitura e gravação do arquivo.
- Considerar um formato estruturado, como CSV ou JSON, se o projeto precisar evoluir.
9. Estrutura de arquivos observada
projeto/
├── consumo_campus.txt
└── README.md
Essa é apenas uma representação dos arquivos fornecidos e da documentação sugerida. O arquivo Python principal e a estrutura completa do projeto não foram enviados, portanto não estão representados aqui.
10. Resumo
O Sistema Monitor Ecocampus mantém registros de consumo por local, permite adicionar novos dados e consultar um local específico. Na consulta, compara o consumo medido com o limite recomendado e apresenta o percentual de excesso. No exemplo da Faculdade, o consumo de 2.000 litros ultrapassa o limite de 1.500 litros em 33,33%.

Para documentar a implementação com precisão — incluindo funções, estruturas de decisão, tratamento de arquivos e regras de classificação — é necessário analisar também o código-fonte da aplicação.
