using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour {

	public bool atRight; //this tracks player position
	public bool active; //this tracks if movement is frozen
	public bool paused; //This tracks if the game is paused or not

	public GameObject pausedMenu; //this is the pause menu gameobject

	// Use this for initialization
	void Start () {
		transform.position = new Vector2(2.5f,-2.8f);
		atRight = true;
		active = true;
		paused = false;
	}
	
	// Update is called once per frame
	void Update () {
		if(Input.GetKeyDown(KeyCode.RightArrow) && !atRight && active) //If player is on left and chooses to go right
		{
			transform.position = new Vector2(2.5f,-2.8f); //Change position to right
			transform.rotation = Quaternion.Euler(Vector3.up * 180); //Rotate to face into center
			atRight = true; //Update variable
		}
		if(Input.GetKeyDown(KeyCode.LeftArrow) && atRight && active) //If player is on right and chooses to go left
		{
			transform.position = new Vector2(-2.5f,-2.8f); //Change position to left
			transform.rotation = Quaternion.Euler(Vector3.up * 360); //Rotate to face into center
			atRight = false; //Update variable
		}

		if(Input.GetKeyDown(KeyCode.P))
		{
			if(paused)
			{
				paused = false; //toggle value
				pausedMenu.active = false; //set menu deactive
				Time.timeScale = 1f; //set time change to 1
			}
			else
			{
				paused = true; //toggle value
				pausedMenu.active = true; //set menu active
				Time.timeScale = 0f; //set time change to 0
			}
		}
	}

	public void pauseFalse()
	{
		paused = false;
		return;
	}
}
