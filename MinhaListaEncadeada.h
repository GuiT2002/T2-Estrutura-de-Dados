#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 * 
 * @tparam T O tipo dos dados armazenados na lista.
 */
template<typename T>
class MinhaListaEncadeada: public ListaEncadeadaAbstrata<T>
{
    
    
    /**
     * @brief Destrutor. Destroi todos os elementos da lista
     */
    virtual ~MinhaListaEncadeada(){
        //escreva o algoritmo esperado
        Elemento<T>* atual = this->_primeiro;
        Elemento<T>* proximo = nullptr;
        
        while (atual != nullptr) {
            proximo = atual->proximo;
            delete atual;
            atual = proximo;
        }
        
        this->_primeiro = nullptr;
        this->_tamanho = 0;
    }

    /**
     * @brief Obtém a quantidade de itens na lista.
     * 
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t tamanho() const
    {
        //substitua a linha abaixo pelo algoritmo esperado
        return this->_tamanho;
    };
    
    /**
     * @brief Indica se há algum item na lista ou não.
     * 
     * @return false se houver algum item na lista; true caso contrário.
     */
    virtual bool vazia() const 
    {
        //substitua a linha abaixo pelo algoritmo esperado
        if (tamanho() == 0) return true;
        else return false;
    };

    /**
     * @brief Obtém a posição de um item na lista. Lança
     * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item cuja posição deseja-se obter.
     * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
     * item na lista, a posição da primeira ocorrência.
     */
    virtual std::size_t posicao(T dado) const 
    {
        //substitua a linha abaixo pelo algoritmo esperado
        if(vazia()) {
            throw ExcecaoListaEncadeadaVazia();
        }

        std::size_t posicao = 0;
        
        Elemento<T>* primeiro = this->_primeiro;
        
        while(primeiro != nullptr) {
            if(primeiro->dado == dado) {
                return posicao;
            }
            posicao++;
            primeiro = primeiro->proximo;
        }
    
        throw ExcecaoDadoInexistente();

    };
    
    /**
     * @brief Indica se um dado item está contido na lista ou não.
     * 
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    virtual bool contem(T dado) const
    {
        //substitua a linha abaixo pelo algoritmo esperado
        Elemento<T>* atual = this->_primeiro;
        while (atual != nullptr) {
            if (atual->dado == dado) {
                return true;
            }
            atual = atual->proximo;
        }
        return false;
    };

    /**
     * @brief Insere um item no início da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoInicio(T dado) 
    {
        //escreva o algoritmo esperado
        Elemento<T>* novoElemento = new Elemento<T>(dado);
        
        novoElemento->proximo = this->_primeiro;
        this->_primeiro = novoElemento;

        this->_tamanho++;
    };

    /**
     * @brief Insere um item em uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa
     * [0, tamanho].
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho]. Ao se inserir em
     * uma posição já ocupada, a posição do item que já estava naquela posição
     * será posicao + 1; inserir-se na posicao tamanho significa inserir-se no
     * fim da lista.
     * @param dado O item sendo inserido.
     */
    virtual void inserir(std::size_t posicao, T dado)
    {
        //escreva o algoritmo esperado
        if ((posicao<0) || (posicao > tamanho())){
            throw ExcecaoPosicaoInvalida();
        }
        
        else if (posicao == 0) {
            inserirNoInicio(dado);
        }
        
        else if (posicao == tamanho()){
            inserirNoFim(dado);
        }
        
        else {
            Elemento<T>* novoElemento = new Elemento<T>(dado);
            Elemento<T>* atual = this->_primeiro;

            for (std::size_t i = 0; i < posicao-1; i++){
                atual = atual->proximo;
            }
            
            novoElemento->proximo = atual->proximo;
            atual->proximo = novoElemento;
            this->_tamanho++;
        }
    };


    /**
     * @brief Insere um item no fim da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoFim(T dado)
    {
        //escreva o algoritmo esperado
    
        if (vazia()) {
            inserirNoInicio(dado);
        }
        
        else{
            Elemento<T>* novoElemento = new Elemento<T>(dado);
            Elemento<T>* atual = this->_primeiro;
            
            while (atual->proximo != nullptr) {
                atual = atual->proximo;
            }
            
            atual->proximo = novoElemento;
            
            this->_tamanho++;
        }
    };

    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoInicio()
    {
        //substitua a linha abaixo pelo algoritmo esperado
        if (vazia()){
            throw ExcecaoListaEncadeadaVazia();
        }
        Elemento<T>* elementoRemovido = this->_primeiro;
        this->_primeiro = this->_primeiro->proximo;
        
        this->_tamanho--;
        
        return elementoRemovido->dado;
    };

    /**
     * @brief Remove um item de uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho).
     * @return O item removido.
     */
    virtual T removerDe(std::size_t posicao)
    {
        //substitua a linha abaixo pelo algoritmo esperado
        if ((posicao < 0) || (posicao >= tamanho())){
            throw ExcecaoPosicaoInvalida();
        }
        
        if (posicao == 0) return removerDoInicio();
        
        else if (posicao == tamanho() - 1) return removerDoFim();
        
        else {
            Elemento<T>* anterior = this->_primeiro;
            //Elemento<T>* proximo;
            for (std::size_t i = 0; i < posicao-1; i++){
                anterior = anterior->proximo;
            }
            
            Elemento<T>* atual = anterior->proximo;
            T elementoRemovido = atual->dado;
            anterior->proximo = atual->proximo;
            delete atual;
            
            this->_tamanho--;
            if (tamanho() == 0) this->_primeiro = nullptr;
            return elementoRemovido;
        }
        
    };

    /**
     * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoFim()
    {
        //substitua a linha abaixo pelo algoritmo esperado
        if (vazia()){
            throw ExcecaoListaEncadeadaVazia();
        }
        
        else{
            Elemento<T>* anterior = nullptr;
            Elemento<T>* atual = this->_primeiro;
            
            while (atual->proximo != nullptr) {
                anterior = atual;
                atual = atual->proximo;
            }
            
            T elementoRemovido = atual->dado;
            delete atual;
            
            if (anterior == nullptr) {
                this->_primeiro = nullptr;
            } else {
                anterior->proximo = nullptr;
            }
            
            this->_tamanho--;
            if (tamanho() == 0) this->_primeiro = nullptr;
            return elementoRemovido;
        }
    };

    /**
     * @brief Remove um item específico da lista. Lança
     * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorrência.
     */
    virtual void remover(T dado)
    {
        //escreva o algoritmo esperado
        if (vazia()) {
            throw ExcecaoListaEncadeadaVazia();
            
        }
        
        else if (!contem(dado)) {
            throw ExcecaoDadoInexistente();
        }
        
        else if (posicao(dado) == tamanho()-1) removerDoFim();
        else if (posicao(dado) == 0) removerDoInicio();
        else{
            Elemento<T>* anterior = this->_primeiro;
            Elemento<T>* atual;
            
            for (std::size_t i = 0; i < posicao(dado) - 1; i++){
                anterior = anterior->proximo;
            }
            
            atual = anterior->proximo;
            anterior->proximo = atual->proximo;
            delete atual;
            
            this->_tamanho--;
            
            if (tamanho() == 0) this->_primeiro = nullptr;
        } 
        
    }; 
    
};

#endif
















