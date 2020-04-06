using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockSpawner : MonoBehaviour {

	public GameObject treeOrig; //Prefab items
	public GameObject treeLongLeft;
	public GameObject treeLongRight;
	public GameObject treeShortLeft;
	public GameObject treeShortRight;

	public float spawnQueue; //Queue of numbers
	private int generateNumber; //Number randomly generated

	public int difficulty; //This is the difficulty setting

	public List<GameObject> treePieces;
	private GameObject tempObj; //This is a temporary 

	int countdown; //This counts down before updating difficulty
	bool firstOne; //Tells if log spawned is first one

	bool recentRight; //recently did right
	bool recentLeft; //recently did left

	// Use this for initialization
	void Start () {
		List<GameObject> treePieces = new List<GameObject>(); //This list is composed of the tree components

		spawnQueue = 10;
		difficulty = 6;
		countdown = 0;
		firstOne = true;
	}
	
	// Update is called once per frame
	void Update () {

		countdown --; //always reduce counter

		//if something in queue and countdown is over
		if(spawnQueue > 0 && countdown < 0 && !firstOne)
		{
			//Generate random number
			generateNumber = Random.Range(0, difficulty);

			//Spawn appropriate block
			if(generateNumber - (difficulty - 2) < 0)
			{
				//spawn normal
				tempObj = Instantiate(treeOrig);
				treePieces.Add(tempObj); //Add to list

				//updating recent values
				recentRight = false;
				recentLeft = false;
			}
			else if(generateNumber - (difficulty - 2) == 0)
			{
				//spawn right branch
				if(Random.Range(0, 2) == 1 && !recentLeft || recentRight)
				{
					tempObj = Instantiate(treeLongRight);
					treePieces.Add(tempObj); //Add to list

					//updating recent values
					recentRight = true;
					recentLeft = false;
				}
				else if(!recentRight)
				{
					tempObj = Instantiate(treeLongLeft);
					treePieces.Add(tempObj); //Add to list

					//updating recent values
					recentRight = false;
					recentLeft = true;
				}
			}
			else if(generateNumber - (difficulty - 2) > 0)
			{
				//spawn left branch
				if(Random.Range(0, 2) == 1 && !recentLeft || recentRight)
				{
					tempObj = Instantiate(treeShortRight);
					treePieces.Add(tempObj); //Add to list

					//updating recent values
					recentRight = true;
					recentLeft = false;
				}
				else if(!recentRight)
				{
					tempObj = Instantiate(treeShortLeft);
					treePieces.Add(tempObj); //Add to list

					//updating recent values
					recentRight = false;
					recentLeft = true;
				}
			}
			spawnQueue --; //Decrease queue by 1
			countdown = 20; //reset countdown
		}
		else if(firstOne && countdown < 0)
		{
			//spawn normal
			tempObj = Instantiate(treeOrig);
			treePieces.Add(tempObj); //Add to list

			spawnQueue --; //Decrease queue by 1
			countdown = 20; //reset countdown
			firstOne = false; //Set first one off
		}
	}
}
