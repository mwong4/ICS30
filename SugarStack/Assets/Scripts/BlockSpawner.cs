using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockSpawner : MonoBehaviour {

	public GameObject treeOrig; //Prefab items
	public GameObject treeRight;
	public GameObject treeLeft;

	public int spawnQueue; //Queue of numbers
	private int generateNumber; //Number randomly generated

	public int difficulty; //This is the difficulty setting

	public List<GameObject> treePieces;
	private GameObject tempObj; //This is a temporary 

	int countdown;

	// Use this for initialization
	void Start () {
		List<GameObject> treePieces = new List<GameObject>(); //This list is composed of the tree components

		spawnQueue = 10;
		difficulty = 6;
		countdown = 0;
	}
	
	// Update is called once per frame
	void Update () {

		countdown --; //always reduce counter

		//if something in queue and countdown is over
		if(spawnQueue > 0 && countdown < 0)
		{
			//Generate random number
			generateNumber = Random.Range(0, difficulty);

			//Spawn appropriate block
			if(generateNumber - (difficulty - 2) < 0)
			{
				//spawn normal
				tempObj = Instantiate(treeOrig);
				treePieces.Add(tempObj); //Add to list
			}
			else if(generateNumber - (difficulty - 2) == 0)
			{
				//spawn right branch
				tempObj = Instantiate(treeRight);
				treePieces.Add(tempObj); //Add to list
			}
			else if(generateNumber - (difficulty - 2) > 0)
			{
				//spawn left branch
				tempObj = Instantiate(treeLeft);
				treePieces.Add(tempObj); //Add to list
			}
			spawnQueue --; //Decrease queue by 1
			countdown = 20; //reset countdown
		}
	}
}
