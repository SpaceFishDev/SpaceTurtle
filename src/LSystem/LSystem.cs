using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.IO;

namespace LSystem{
	class LSys{
		public string Rule;
		public string Subst;
		public LSys(string Rule, string Subst){
			this.Rule = Rule.ToLower();
			this.Subst = Subst.ToLower();
		}
		public string ApplyRule(string text){
			string result = "";
			for(int i = 0; i < text.Length; ++i){
				if(text[i] == Rule[0]){
					for(int j = 0; j != Rule.Length && j + i != text.Length; ++j){
						if(Rule[j] != text[j + i]){
							break;
						}
					}
					result += Subst;
					i += Rule.Length - 1;
					goto skip;
				}
				result += text[i];
				skip:;
			}
			return result;
		}	
	}
	class Program{
		[DllImport("msvcrt.dll")]
		static extern int system(string f);

		static void Main(string[] Args){

			if(Args.Length == 0){
				Console.WriteLine("Please provide Source File.");
				return;
			}
			List<LSys> systems = new List<LSys>();
			systems.Add(new LSys("f","F[-F[+F][-F]+F[-F][+F]]"));
			string new_arg = File.ReadAllText(Args[0]).ToLower();
			for(int i = 0; i != 5; ++i){
				for(int x = 0; x != systems.Count; ++x){
					new_arg = systems[x].ApplyRule(new_arg);
				}
			}
			LSys s = new LSys("x", "F");
			new_arg = s.ApplyRule(new_arg);
			Console.WriteLine($"OUTPUT:\n{new_arg}");

			File.WriteAllText("out.turt", new_arg);
			system($"spt out.turt");
		}
	}
}