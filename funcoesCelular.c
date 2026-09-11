case 2: {
                printf("Lista Celulares\n");
                
                for (int i = 0; i < qtdCelulares; i++)
                    printf("%d - %d - %f\n", listaCelulares[i].id, listaCelulares[i].ano, listaCelulares[i].preco);

                break;
            }
            case 3: {
                printf("Atualizar");
                printf("Lista Celulares\n");
                for (int i = 0; i < qtdCelulares; i++)
                    printf("%d - %d - %f\n", listaCelulares[i].id, listaCelulares[i].ano, listaCelulares[i].preco);
                printf("Digite o id do celular: \n");
                int id;
                scanf("%d", &id);
                int achou = 0;
                for (int i = 0; i < qtdCelulares; i++){
                    if (id == listaCelulares[i].id){
                        printf("Digite o ano: ");
                        scanf("%d", &listaCelulares[i].ano);
                        printf("Digite o Preço: ");
                        scanf("%f", &listaCelulares[i].preco);
                        achou = 1;
                        break;
                    }
                }
                if (!achou) printf("Celular não encontrado!\n");
                else printf("Celular atualizado com sucesso \n");

                break;
            }
