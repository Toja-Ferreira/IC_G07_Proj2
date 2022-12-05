# IC_G07_Proj2
### Projeto 2 da cadeira de Informação e Codificação de MECT

Parte I do projeto localizada na pasta [**Part_I**](Part_I): <br>

      1. Compilar (necessário estar no diretório ../Part_I) 
         * cmake .
         * make

      2. Testar (necessário estar no diretório ../Part_I/test_programs) 
         * ./copyImage lena.ppm lenaCopy.ppm                                  -> testar copiar imagem
         * ./negativeImage lena.ppm lenaNegative.ppm                          -> testar imagem negativa
         * ./mirrorImage lena.ppm lenaVertical.ppm V                          -> testar espelhar verticalmente
         * ./rotateImage lena.ppm lenaRotate.ppm -90                          -> testar rodar imagem -90º
         * ./intensityImage lena.ppm lenaIntensity.ppm 100                    -> testar mudar intensidade de luz por 100
  <br>

Parte II do projeto localizada na pasta [**Part_II**](Part_II): <br>
    
      1. Compilar (necessário estar no diretório ../Part_II) 
         * cmake .
         * make

      2. Testar (necessário estar no diretório ../Part_II/test_programs) 
         * ./test
       
  <br>
  
Parte III do projeto localizada na pasta [**Part_III**](Part_III): <br>
    
      1. Compilar (necessário estar no diretório ../Part_III) 
         * cmake .
         * make

      2. Testar (necessário estar no diretório ../Part_III/test_programs) 
         * ./testEncoding sample01.wav compressed01 1 0 0                    -> testar codificação lossless de ordem 1
         * ./testEncoding sample01.wav compressed01 2 1 3                    -> testar codificação lossy (cortando 3 bits) de ordem 2
         * ./testDecoding compressed01 decompressed 1 0 0                    -> testar descodificação
       
  <br>
  
Part IV do projeto localizada na pasta [**Parte_IV**](Parte_IV) contém a implementação do Lossless Image Codec e pasta com ficheiros de teste: <br>

    1. Compilar (necessário estar no diretório ../Parte_IV) 
       * make

    2. Testar (necessário estar no diretório ../Parte_IV) 
       * ../bin/test_image_codec -e lena.ppm output                          -> testar codificação
       * ../bin/test_image_codec -d output new_image.ppm                     -> testar descodificação
       
  <br>
   
Part V do projeto contida no relatório [**IC_G07_Proj1.pdf**](IC_G07_Proj2.pdf) 
