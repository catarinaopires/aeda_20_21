#include "parque.h"

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli): numMaximoClientes(nMaxCli), lotacao(lot){
    vagas = lot;
}

unsigned ParqueEstacionamento::getNumLugares() const{
    return lotacao;
}

unsigned ParqueEstacionamento::getNumMaximoClientes() const{
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const{

    for(int i = 0; i < clientes.size(); i++){
        if(clientes[i].nome == nome)
            return i;
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome){
    if(clientes.size() < numMaximoClientes){
        InfoCartao cliente;
        cliente.nome = nome;
        cliente.presente = false;

        clientes.push_back(cliente);

        return true;
    }
    return false;
}

bool ParqueEstacionamento::entrar(const string & nome){

    // Verificar se parque está completo
    if(vagas == 0){
        return false;}
    else{
        // Verificar se está regitado e se já está dentro do parque
        for(int i = 0; i < clientes.size(); i++){
            if(clientes[i].nome == nome && !clientes[i].presente){
                clientes[i].presente = true;    // Registrar entrada
                vagas--;
                return true;
            }
        }
    }
    return false;
}

bool ParqueEstacionamento::retiraCliente(const string & nome){

    for(int i = 0; i < clientes.size(); i++){

        // Remoção só é possível se este estiver atualmente fora do parque
        if(clientes[i].nome == nome && !clientes[i].presente){
            clientes.erase (clientes.begin()+i);
            return true;
        }
    }
    return false;
}

bool ParqueEstacionamento::sair(const string & nome){
    // Não está registado
   if (posicaoCliente(nome) == -1)
       return false;
   else{
       // Viatura não está dentro do parque
       if(!clientes[posicaoCliente(nome)].presente)
           return false;
       else{
           // Regista saída de cliente
           clientes[posicaoCliente(nome)].presente = false;
           vagas++;
           return true;
       }
   }
}

unsigned ParqueEstacionamento::getNumLugaresOcupados() const{
    return (lotacao-vagas);
}

unsigned ParqueEstacionamento::getNumClientesAtuais() const{
    return clientes.size();
}
