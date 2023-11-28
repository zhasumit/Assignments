package Quiz;

import java.util.Arrays;

import Quiz.CompleteQuestion;

@SuppressWarnings("serial")
public class CompleteQuestionImpl extends CompleteQuestion {

	public CompleteQuestionImpl() {
	}
	
	public CompleteQuestionImpl(String sentence, Answer answers[], char[] correctAnswers) {
		this.sentence = sentence;
		this.answers = answers;
		this.correctAnswers = correctAnswers;
	}

	@Override
	public String toString() {
		return "CompleteQuestionImpl [correctAnswers="
				+ Arrays.toString(correctAnswers) + ", id=" + id
				+ ", sentence=" + sentence + ", answers="
				+ Arrays.toString(answers) + "]";
	}
	
}
