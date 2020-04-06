using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CutTree : MonoBehaviour {

	public bool active;

	public BlockSpawner blockSpawner; //Spawner script
	public DisplayPoints displayPoints; //points display script
	public TimerScript timerScript; //timer script
	public int points; //Points storer
	public int counter; //this is for knowing when to increase difficulty

	public Sprite idleImage; //This is idle image
	public Sprite swingImage; //This frame for when axe is used 

	public float force;

	float countdown; //cooldown for animation

	// Use this for initialization
	void Start () {
		points = 0; //Points start at 0
		counter = 10; //Counter starts at 10
		active = true;
		this.gameObject.GetComponent<SpriteRenderer>().sprite = idleImage;
	}
	
	// Update is called once per frame
	void Update () {
		countdown --;

		if(Input.GetKeyDown(KeyCode.Space) && active)
		{
			this.gameObject.GetComponent<SpriteRenderer>().sprite = swingImage;
			countdown = 5;
			//check if grounded
			if(blockSpawner.treePieces[0].GetComponent<IsGrounded>().grounded == true)
			{
				blockSpawner.treePieces[0].GetComponent<IsGrounded>().destroyed = true; //Set branch to destroyed
				Destroy(blockSpawner.treePieces[0], 0.1f); //if yes -> destory
				force = 25.0f + 4.0f*(10.0f-blockSpawner.spawnQueue);//calculate force
				blockSpawner.treePieces[0].GetComponent<Rigidbody2D>().AddForce(transform.right * force, ForceMode2D.Impulse); //Use force

				blockSpawner.treePieces.RemoveAt(0); //pop spot on list
				
				blockSpawner.spawnQueue ++;//spawn new tree
				counter ++; //increase counter
				points ++;//add point
				displayPoints.displayPoints(points);//display time
				timerScript.countdown += 90; //add to time

				//Check for difficulty update
				if(counter % 20 == 0 && blockSpawner.difficulty > 3)
				{
					timerScript.takeAway = 4;
					counter = 1; //reset counter
					blockSpawner.difficulty --; //increase (decrease regular spawning) difficulty
				}
			}
		}

		if(countdown <= 0)
		{
			this.gameObject.GetComponent<SpriteRenderer>().sprite = idleImage;
		}
	}
}


