using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TimerScript : MonoBehaviour {

	public float countdown; //If this reaches 0, game ends
	public Image timeBar;

	// Use this for initialization
	void Start () {
		countdown = 1000;
	}
	
	// Update is called once per frame
	void Update () {
		countdown --;
		timeBar.fillAmount = countdown / 1000;

		if(countdown < 0) //If time is out
		{
			//trigger game over
			Debug.Log("Game Over");
		}
		else if(countdown > 1000)
		{
			//if too much time
			countdown = 1000;
			//reset to 1000
		}
	}
}
