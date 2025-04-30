# Atividade-Avaliativa-A2
Trabalho com dois exercícios: Sistema de Gerenciamento de Usuários com Árvore AVL e Sistema de Inventário com Árvore Rubro-Negra

1) Sistema de Gerenciamento de Usuários com Árvore AVL (1 pt)

Objetivo: Desenvolver um sistema que gerencie usuários utilizando uma árvore AVL para armazenar e organizar os dados dos usuários. O sistema deve permitir as operações de cadastro, remoção, busca e listagem em ordem alfabética.
Descrição do Sistema: O sistema deve armazenar as informações dos usuários, como:
Nome (chave para a organização na árvore).
ID único.
E-mail.
A estrutura da árvore AVL será usada para garantir que os usuários sejam armazenados e acessados de forma eficiente, com balanceamento automático após alterações.

Requisitos Funcionais:
Cadastrar Usuário: Adicionar um novo usuário à árvore AVL. Após o cadastro:
Atualizar alturas e fatores de balanceamento.
Realizar rotações para manter o balanceamento.
Remover Usuário: Remover um usuário a partir de seu nome. Após a remoção: Reequilibrar a árvore se necessário.
Buscar Usuário: Permitir a busca por um usuário pelo nome. Retorne os dados do usuário se encontrado.
Listar Usuários em Ordem Alfabética: Percorrer a árvore em ordem e listar os usuários em ordem alfabética pelo nome.


2) Sistema de Inventário com Árvore Rubro-Negra (1pt)

Objetivo: Desenvolver um sistema de inventário para gerenciar produtos usando uma Árvore Rubro-Negra, que organiza os produtos com base em um código único. O sistema deve oferecer operações eficientes de cadastro, remoção e busca, utilizando as propriedades da Árvore Rubro-Negra.
Descrição do Sistema: O sistema deve armazenar informações de cada produto, como:
Código do produto (chave para organização na árvore).
Nome do produto.
Quantidade em estoque.
Preço por unidade.
A Árvore Rubro-Negra será usada para armazenar os produtos de forma balanceada, garantindo que as operações sejam realizadas em tempo logarítmico.

Requisitos Funcionais:
Cadastrar Produto: Adicionar um novo produto à árvore. Após o cadastro:
Verifique as propriedades da Árvore Rubro-Negra (como cores dos nós e balanceamento).
Faça ajustes necessários com rotações e mudanças de cor.
Remover Produto: Remover um produto do inventário baseado no código. Após a remoção: Verifique e mantenha as propriedades da Árvore Rubro-Negra.
Buscar Produto: Buscar um produto na árvore com base no código do produto e exibir suas informações, se encontrado.
Listar Produtos: Percorrer a árvore em ordem (in-order traversal) e listar os produtos de forma ordenada pelo código.
