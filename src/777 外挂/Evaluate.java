import javax.script.ScriptEngineManager;
import javax.script.ScriptEngine;
public class Main {
	public static void main(String[] args) throws Exception {
		ScriptEngineManager mgr = new ScriptEngineManager();
		ScriptEngine engine = mgr.getEngineByName("JavaScript");
		String foo = "3+4";
		System.out.println(engine.eval(foo));
	}
}