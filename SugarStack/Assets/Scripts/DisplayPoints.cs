using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DisplayPoints : MonoBehaviour {

	public Text textBox;

	public void displayPoints(int _input)
	{
		textBox.text = "Points: " + _input;
	}
}
