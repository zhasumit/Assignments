package Quiz;

import java.util.Arrays;

import Quiz.Question;

@SuppressWarnings("serial")
public class QuestionImpl extends Question {

	public QuestionImpl() {
	}
	
	public QuestionImpl(int id, String sentence, Answer answers[]) {
		this.id = id;
		this.sentence = sentence;
		this.answers = answers;
	}

	@Override
	public String toString() {
		return "QuestionImpl [id=" + id + ", sentence=" + sentence
				+ ", answers=" + Arrays.toString(answers) + "]";
	}
}
