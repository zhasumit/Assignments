package client;

import java.io.*;
import org.omg.CORBA.ORB;
import org.omg.CosNaming.NamingContextExt;
import org.omg.CosNaming.NamingContextExtHelper;

import Quiz.AnswerImpl;
import Quiz.Answer;
import Quiz.CompleteQuestion;
import Quiz.CompleteQuestionImpl;
import Quiz.Question;
import Quiz.QuestionHolder;
import Quiz.QuizServerHelper;
import Quiz.QuizServerOperations;
import Quiz.QuizServerPackage.QuizException;
import Quiz.QuizServerPackage.answersIdsHolder;

public class QuizClientInteractive {

	private static QuizServerOperations serverImpl;
	private static BufferedReader reader;
	
	public static final String SERVER_NAME = "Quiz";	
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try{
			// create and initialize the ORB
			ORB orb = ORB.init(args, null);

			// get the root naming context
			org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
			// Use NamingContextExt instead of NamingContext. This is 
			// part of the Interoperable naming Service.  
			NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);

			// resolve the Object Reference in Naming
			serverImpl = QuizServerHelper.narrow(ncRef.resolve_str(SERVER_NAME));
			
			/*
			 * Start
			 */
			System.out.println("Welcome to the Quiz Client.");
			reader = new BufferedReader(new InputStreamReader(System.in));
			showMenuDialog();
            
		} catch (Exception e) {
			System.out.println("ERROR : " + e) ;
			e.printStackTrace(System.out);
		}	
	}
	private static void showMenuDialog(){
		try {
			
			System.out.println("\n------ Please choose an option:");
	    	System.out.println("a: Insert a new question");
	    	System.out.println("b: Request a random question");
	    	System.out.println("c: Remove a question");
	    	
	        String option = reader.readLine();
	        
	        switch(option) {
		        case "a": insertQuestion(); break;
		        case "b": newRandomQuestion(); break;
		        case "c": removeQuestion(); break;
		        default: returnToMenu(); break;
	        }
	        
		} catch(IOException e) {
        	System.out.println("IOException " + e);
        } catch(QuizException e) {
        	System.out.println("QuizException " + e);
        } catch(Exception e) {
        	System.out.println("Exception " + e);
        }
        
	}
	
	/**
	 * Remove a question.
	 * 
	 * @throws IOException
	 * @throws QuizException
	 */
	private static void removeQuestion() throws IOException, QuizException {
		System.out.println("Write the ID of the question that you would like to remove");
		int questionId = readInteger();
		serverImpl.deleteQuestion(questionId);
			
		returnToMenu();
	}
	
	/**
	 * Get a random question and answer it.
	 * 
	 * @throws IOException
	 * @throws QuizException
	 */
	private static void newRandomQuestion() throws IOException, QuizException {
			System.out.println("------ Request Question");
			
			/*
			 * Get random question from server
			 */
			QuestionHolder myQuestionHolder = new QuestionHolder();
			serverImpl.getQuestion(myQuestionHolder);
			Question receivedQuestion = myQuestionHolder.value;
			
			/*
			 * Print question and alternatives
			 */
			System.out.println("The question is: " + receivedQuestion.sentence);
			Answer[] answers = receivedQuestion.answers;
			for(int i=0; i<answers.length; i++) {
				System.out.println(answers[i].id + ": " + answers[i].sentence);
			}
			
			/*
			 * Answer question
			 */
			System.out.println("Which is the correct answer? Write the letters followed by a comma (,) in order if there are more than one correct answer");
			String correctAnswers = reader.readLine();
			String[] correct = correctAnswers.split(",");
			char[] correctA = new char[correct.length];
			
			for (int i=0; i < correct.length; i++) {
				correctA[i] = correct[i].charAt(0);
			}
			answersIdsHolder correctAnswersHolder = new answersIdsHolder();
			boolean answerIsCorrect = serverImpl.answerQuestion(receivedQuestion.id, correctA, correctAnswersHolder);
			if(answerIsCorrect) {
				System.out.println("Correct answer!");
			} else { 
				System.out.println("You're wrong, I'm sorry! These are the correct answers:");
				System.out.println(correctAnswersHolder.value);
			}
			
			returnToMenu();		
	}
	
	
	private static void insertQuestion() throws IOException, QuizException {
	        System.out.println("------ Insert your new question:");
	        String question = reader.readLine();
	        
	        int howManyAlt = 0;
	        String alternative = null;
	        int howManyCorr = 0;
	        //int count = 0;
	        char[] myCorrectAlternatives = new char[0];
	        int currcount = 0;
	        Answer[] alternatives = new Answer[0];
	   
	        
        	System.out.println("How many alternative would you like to insert? ");
	        howManyAlt = readInteger();
	        
	        alternatives= new Answer[howManyAlt];
	        
	        System.out.println("How many alternative are correct? ");
	        howManyCorr = readInteger();			        
	        myCorrectAlternatives = new char[howManyCorr];	        
	        
	        for(int count = 0; count < howManyAlt; count++) {
		        System.out.println("Write your alternative! ");
			    alternative = reader.readLine();
		        alternatives[count] = new AnswerImpl(((char)(count+65)), alternative);
		        
		        if (currcount < howManyCorr) {
			        System.out.println("Is it correct? Y or N ");
				    if(readYes()){
				    	myCorrectAlternatives[currcount] = ((char)(count+65));
				    	currcount ++;
				    }
		        }
	        }

	        /*
	         * Create question and send it to the server
	         */
	        CompleteQuestion myQuestion = new CompleteQuestionImpl(question, alternatives, myCorrectAlternatives);
	    	int receivedQuestionId = serverImpl.insertQuestion(myQuestion);
	    	System.out.println("> reseived question id: " + receivedQuestionId);
	    	
	    	returnToMenu();
	}

	/**
	 * Shows dialog to return to the menu or quit.
	 * 
	 * @throws IOException
	 */
	private static void returnToMenu() throws IOException {
		System.out.println("Would you like to do somenthing else? Y or N");
    	if(readYes()){
    		showMenuDialog();
    	} else {
    		System.out.println("Goodbye. Quit.");		
    	}
	}
	
	/**
	 * Reads a line and pares it to an integer.
	 * 
	 * @return Read integer
	 * @throws IOException
	 */
	private static int readInteger() throws IOException {
		try {
			return Integer.parseInt(reader.readLine());
		} catch (NumberFormatException e) {
			System.err.println("NumberFormatException: Could not parse integer");
			return -1;
		}		
	}
	
	/**
	 * Returns true, when a "Y" or "y" is read.
	 * 
	 * @return True, when read "Y" or "y"
	 * @throws IOException
	 */
	private static boolean readYes() throws IOException {
    	String line = reader.readLine().toLowerCase();
    	return line.equals("y");
	}
	
}
