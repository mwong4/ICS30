using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CutTree : MonoBehaviour {

	public BlockSpawner blockSpawner; //Spawner script
	public DisplayPoints displayPoints; //points display script
	public TimerScript timerScript; //timer script
	public int points; //Points storer
	public int counter; //this is for knowing when to increase difficulty

	// Use this for initialization
	void Start () {
		points = 0; //Points start at 0
		counter = 10; //Counter starts at 10
	}
	
	// Update is called once per frame
	void Update () {
		if(Input.GetKeyDown(KeyCode.Space))
		{
			Debug.Log("Space");
			Debug.Log(blockSpawner.treePieces[0].GetComponent<IsGrounded>().grounded);

			//check if grounded
			if(blockSpawner.treePieces[0].GetComponent<IsGrounded>().grounded == true)
			{
				Destroy(blockSpawner.treePieces[0]); //if yes -> destory
				blockSpawner.treePieces.RemoveAt(0); //pop spot on list
				
				blockSpawner.spawnQueue ++;//spawn new tree
				counter ++; //ncrease counter
				points ++;//add point
				displayPoints.displayPoints(points);//display time
				timerScript.countdown += 50; //add to time

				//Check for difficulty update
				if(counter % 30 == 0 && blockSpawner.difficulty > 2)
				{
					counter = 1; //reset counter
					blockSpawner.difficulty --; //increase (decrease regular spawning) difficulty
				}
			}
		}
	}
}


