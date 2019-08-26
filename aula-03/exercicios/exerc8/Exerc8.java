/**
 * Exerc8
 */
public class Exerc8 {

    public static void main(String args[]) {
        FichaDeAluno aluno = new FichaDeAluno();
        aluno.setNome("Pedro");
        aluno.setDisciplina("Ciências da Computação");
        aluno.setNotaProva1(8.5f);
        aluno.setNotaProva2(9f);
        System.out.println(aluno.toString());
    }
}