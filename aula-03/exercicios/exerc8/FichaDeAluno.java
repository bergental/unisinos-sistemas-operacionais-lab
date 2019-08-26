public class FichaDeAluno {

    private String nome;
    private String disciplina;
    private float notaProva1;
    private float notaProva2;

    public FichaDeAluno() {
        super();
    }
    
    public FichaDeAluno(String nome, String disciplina, float notaProva1, float notaProva2) {
        super();
        this.nome = nome;
        this.disciplina = disciplina;
        this.notaProva1 = notaProva1;
        this.notaProva2 = notaProva2;
    }

    /**
     * @return the nome
     */
    public String getNome() {
        return nome;
    }

    /**
     * @param nome the nome to set
     */
    public void setNome(String nome) {
        this.nome = nome;
    }

    /**
     * @return the disciplina
     */
    public String getDisciplina() {
        return disciplina;
    }

    /**
     * @param disciplina the disciplina to set
     */
    public void setDisciplina(String disciplina) {
        this.disciplina = disciplina;
    }

    /**
     * @return the notaProva1
     */
    public float getNotaProva1() {
        return notaProva1;
    }

    /**
     * @param notaProva1 the notaProva1 to set
     */
    public void setNotaProva1(float notaProva1) {
        this.notaProva1 = notaProva1;
    }

    /**
     * @return the notaProva2
     */
    public float getNotaProva2() {
        return notaProva2;
    }

    /**
     * @param notaProva2 the notaProva2 to set
     */
    public void setNotaProva2(float notaProva2) {
        this.notaProva2 = notaProva2;
    }

    @Override
    public String toString() {
        StringBuffer sb = new StringBuffer("\n\n--------- Lendo os dados do objeto ---------\n\n");
        sb.append("Nome ...........: "+nome);
        sb.append("\nDisciplina .....: "+disciplina);
        sb.append("\nNota da Prova 1 ...: "+notaProva1);
        sb.append("\nNota da Prova 2 ...: "+notaProva2);
        sb.append("\n");
        return sb.toString();
    }
}