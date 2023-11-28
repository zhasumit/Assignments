package Quiz;

@SuppressWarnings("serial")
public class AnswerImpl extends Answer {

	public AnswerImpl() {
	}
	
	public AnswerImpl(char id, String sentence) {
		this.id = id;
		this.sentence = sentence;
	}

	@Override
	public String toString() {
		return "AnswerImpl [id=" + id + ", sentence=" + sentence + "]";
	}
}
