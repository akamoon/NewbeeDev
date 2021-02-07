using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
public class BundleLoader : MonoBehaviour
{
    public int min = 1;
    public int max = 3;
    public string assetNameBase = "TestObj";
    public string bundleNameBase = "prjprefab";

    public int loadInd = 1;
    void Start()
    {
        string bundlePath = "Bundles/" + bundleNameBase;
        string bundlePath2 = "Bundles/" + bundleNameBase + "2";
        string bundlePath3 = "Bundles/" + bundleNameBase + "2";

        string fullBundlePath = ""; 
        AssetBundle loadAssetBundle = null ;

        for(int i=min;i<=max;++i)
        {
            fullBundlePath = Path.Combine(Application.dataPath, bundlePath + i.ToString());
            loadAssetBundle = AssetBundle.LoadFromFile(fullBundlePath);
        }

        if(loadAssetBundle == null)
        {
            Debug.LogError("Failed to load Assetbundle");
            return;
        }

        string assetName = assetNameBase + loadInd.ToString();
        GameObject asset = loadAssetBundle.LoadAsset<GameObject>(assetName);
        IEnumerable<AssetBundle> bundles = AssetBundle.GetAllLoadedAssetBundles();
        foreach(AssetBundle b in bundles)
        {
            Debug.Log(b.name);
        }
        Instantiate(asset);
        // loadAssetBundle.Unload(true);
    }
}
