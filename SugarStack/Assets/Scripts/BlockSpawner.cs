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

	// Use this for initialization
	void Start () {
		List<GameObject> treePieces = new List<GameObject>(); //This list is composed of the tree components

		spawnQueue = 10;
		difficulty = 6;
	}
	
	// Update is called once per frame
	void Update () {

		//this.gameObject.GetComponent<DisplayPoints>().displayPoints(20000);

		if(spawnQueue > 0)
		{
			//Generate random number
			generateNumber = Random.Range(0, difficulty);

			//Spawn appropriate block
			if(generateNumber - (difficulty - 2) < 0)
			{
				//spawn normal
				Instantiate(treeOrig);
				treePieces.Add(treeOrig); //Add to list
			}
			else if(generateNumber - (difficulty - 2) == 0)
			{
				//spawn right branch
				Instantiate(treeRight);
				treePieces.Add(treeRight); //Add to list
			}
			else if(generateNumber - (difficulty - 2) > 0)
			{
				//spawn left branch
				Instantiate(treeLeft);
				treePieces.Add(treeLeft); //Add to list
			}
			spawnQueue --; //Decrease queue by 1
		}
	}
}
