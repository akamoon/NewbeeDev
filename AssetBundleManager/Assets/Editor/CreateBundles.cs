using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.IO;

public class CreateBundles 
{
    [MenuItem("BundleManager/Build Bundles")]
    static void BuildAllAssetBundles()
    {
        //@TODO add script, see class dependence
        string assetBundleDirectory = "Bundles";
        string bundleFullPath = Path.Combine(Application.dataPath, assetBundleDirectory);
        if (Directory.Exists(bundleFullPath))
        {
            Directory.Delete(bundleFullPath, true);
        }
        Directory.CreateDirectory(bundleFullPath);

        BuildPipeline.BuildAssetBundles(bundleFullPath,
            BuildAssetBundleOptions.None,
            EditorUserBuildSettings.activeBuildTarget);
    }

    static void GetPathAt(string folderPath)
    {
        // AssetDatabase.path
        // https://docs.unity3d.com/ScriptReference/AssetDatabase.FindAssets.html
        // https://forum.unity.com/threads/how-to-get-list-of-assets-at-asset-path.18898/
    }
    
    [MenuItem("BundleManager/Auto Set Name")]
    static void SetAssetBundleName()
    {
        // --@TODO 清理所有不用的bundle name

        string basePath = "Assets/Prefab/TestObj";
        string texturePath = "Assets/Texture/";
        // string basePath = "Assets/Prefab/TestObj";
        string spePath;
        string bundleName;
        for (int i = 1; i < 4; i++)
        {
            spePath = basePath + i.ToString() + ".prefab"; 
            // Debug.Log(spePath);
            bundleName = "PrjPrefab" + i.ToString();
            AssetImporter.GetAtPath(spePath).SetAssetBundleNameAndVariant(bundleName, "");

            spePath = texturePath + i.ToString() + ".jpg"; 
            AssetImporter.GetAtPath(spePath).SetAssetBundleNameAndVariant(bundleName, "");
        }
    }


    [MenuItem("BundleManager/Clean Name")]
    static void CleanBundleName()
    {

    }
}
