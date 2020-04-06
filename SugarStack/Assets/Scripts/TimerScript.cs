using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TimerScript : MonoBehaviour {

	public float countdown; //If this reaches 0, game ends
	public Image timeBar; //Time holding text component
	public float takeAway; //taken away from time

	//referencing player scripts
	public CutTree cutTree; 
	public PlayerController playerController;

	public GameObject restartMenu; //This is the restart menu obj

	// Use this for initialization
	void Start () {
		countdown = 3000;
		takeAway = 3;
	}
	
	// Update is called once per frame
	void Update () {
		countdown -= takeAway;
		timeBar.fillAmount = countdown / 3000;

		if(countdown < 0) //If time is out
		{
			//trigger game over
			restartMenu.SetActive(true);
			cutTree.active = false; //freeze cutting
			playerController.active = false;//freeze movement
		}
		else if(countdown > 3000)
		{
			//if too much time
			countdown = 3000; //reset to 1000
		}
	}
}
