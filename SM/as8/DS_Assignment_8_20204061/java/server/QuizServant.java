package server;


import Quiz.CompleteQuestion;
import Quiz.QuestionHolder;
import Quiz.QuestionImpl;
import Quiz.QuizServerPOA;
import Quiz.QuizServerPackage.QuizException;
import Quiz.QuizServerPackage.answersIdsHolder;

import java.util.*;

public class QuizServant extends QuizServerPOA {

	/** Counter for the question IDs */
	private int numQuestions;
	
	/** Map to save questions */
	private Map<Integer, CompleteQuestion> compleQuestions;

	public QuizServant() {
		this.numQuestions = 0;
		this.compleQuestions = new HashMap<Integer, CompleteQuestion>();
	}

	@Override
	public int insertQuestion(CompleteQuestion question) throws QuizException {
		System.out.println("> receive new question " + question);
		question.id = this.numQuestions++;
		// add to map
		this.compleQuestions.put(question.id, question);
		System.out.println("send question id: " + question.id);
		return question.id;
	}

	@Override
	public boolean getQuestion(QuestionHolder randomQuestion)
			throws QuizException {
		System.out.println("> receive random question request");
		if (!this.compleQuestions.isEmpty()) {
			// Get random complete question
			CompleteQuestion question = this.compleQuestions.get(getRandomMapKey());
			randomQuestion.value = new QuestionImpl(question.id, question.sentence, question.answers);
			System.out.println("send question: " + randomQuestion.value);
			return true;
		} else {
			return false;
		}
	}

	@Override
	public boolean answerQuestion(int questionId, char[] answer,
			answersIdsHolder correct) throws QuizException {

		if (this.compleQuestions.containsKey(questionId)) {
			char[] correctAnswers = compleQuestions.get(questionId).correctAnswers;
			correct.value = correctAnswers;

			// Answer is wrong in this case
			if (answer.length != correctAnswers.length) {
				// System.out.print("Different answer lenght");
				return false;
			}

			boolean flag = true;
			for (int i = 0; i < answer.length; i++) {
				flag = flag & (answer[i] == correctAnswers[i]);
			}
			return flag;

		} else {
			System.err.println("Question ID exits not.");
			return false;
		}

	}

	@Override
	public int deleteQuestion(int questionId) throws QuizException {
		if (this.compleQuestions.containsKey(questionId)) {
			compleQuestions.remove(questionId);
			return questionId;
		} else {
			System.err.println("Quesiton ID exits not.");
			return -1;
		}
	}

	/**
	 * Get a random key from the map this.compleQuestions.
	 * 
	 * @return random map key
	 */
	private Integer getRandomMapKey() {
		List<Integer> mapKeys = new ArrayList<Integer>(this.compleQuestions.keySet());
		int randomIndex = (int) (Math.random() * mapKeys.size());
		return mapKeys.get(randomIndex);
	}

}
